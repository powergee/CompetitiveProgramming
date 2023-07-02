use std::collections::VecDeque;
use std::ptr::{self, null_mut};

const BASE_SYM: char = 'a';
const SYM_CNT: usize = 26;

pub struct Trie {
    next: [*mut Trie; SYM_CNT],
    fail: *mut Trie,
    matched: bool,
}

impl Drop for Trie {
    fn drop(&mut self) {
        for node in self.next {
            if !node.is_null() {
                drop(unsafe { Box::from_raw(node) });
            }
        }
    }
}

impl Trie {
    pub fn new() -> Self {
        Self {
            next: [null_mut(); SYM_CNT],
            fail: null_mut(),
            matched: false,
        }
    }

    pub fn recognize(&self, query: &str) -> bool {
        let mut curr = self;

        for c in query.as_bytes() {
            let next_idx = (*c - BASE_SYM as u8) as usize;
            while !ptr::eq(curr, self) && curr.next[next_idx].is_null() {
                curr = unsafe { &*curr.fail };
            }
            if !curr.next[next_idx].is_null() {
                curr = unsafe { &*curr.next[next_idx] };
            }
            // Report all strings in O[n] as occurring at this point of the text
            if curr.matched {
                return true;
            }
        }
        false
    }

    pub fn enter_in_tree(&mut self, s: &str) {
        let mut curr = self;
        for c in s.as_bytes() {
            let next_idx = (*c - BASE_SYM as u8) as usize;
            if curr.next[next_idx].is_null() {
                curr.enter_child(Trie::new(), next_idx);
            }
            curr = unsafe { &mut *curr.next[next_idx] };
        }
        curr.enter_output(s);
    }

    #[inline]
    fn enter_child(&mut self, child: Self, idx: usize) {
        self.next[idx] = Box::into_raw(Box::new(child));
    }

    #[inline]
    fn enter_output(&mut self, _: &str) {
        self.matched = true;
    }

    pub fn build_failure(&mut self) {
        let mut q: VecDeque<*mut Self> = VecDeque::new();
        self.fail = self;
        q.push_back(self);

        while let Some(curr) = q.pop_front() {
            let curr = unsafe { &*curr };
            for i in 0..SYM_CNT {
                let next = match unsafe { curr.next[i].as_mut() } {
                    Some(ptr) => ptr,
                    None => continue,
                };

                self.complete_failure(next, i);
                q.push_back(next);
            }
        }
    }

    #[inline]
    fn complete_failure(&self, n: &mut Self, c: usize) {
        let np = unsafe { n.next[c].as_mut() }.unwrap();
        let mut m = n;

        while !ptr::eq(m, self) && m.next[c].is_null() {
            m = unsafe { &mut *m.fail };
        }
        if !m.next[c].is_null() {
            m = unsafe { &mut *m.next[c] };
        }
        np.fail = m;
        np.matched = np.matched || m.matched;
    }
}