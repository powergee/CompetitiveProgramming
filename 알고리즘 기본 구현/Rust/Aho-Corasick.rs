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

    pub fn insert(&mut self, str: &str) {
        let bytes = str.as_bytes();
        let mut node = self;
        for i in 0..str.len() {
            let next_idx = (bytes[i] - BASE_SYM as u8) as usize;
            if node.next[next_idx].is_null() {
                node.next[next_idx] = Box::into_raw(Box::new(Trie::new()));
            }
            node = unsafe { &mut *node.next[next_idx] };
        }
        node.matched = true;
    }

    pub fn build_fail(&mut self) {
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

                let mut dest = unsafe { &mut *curr.fail };
                while !ptr::eq(dest, self) && dest.next[i].is_null() {
                    dest = unsafe { &mut *dest.fail };
                }
                if !dest.next[i].is_null() {
                    dest = unsafe { &mut *dest.next[i] };
                }
                next.fail = dest;

                if unsafe { &*next.fail }.matched {
                    next.matched = true;
                }
                q.push_back(next);
            }
        }
    }

    pub fn find(&self, query: &str) -> bool {
        let mut curr = self;
        let query = query.as_bytes();

        for c in 0..query.len() {
            let next_idx = (query[c] - BASE_SYM as u8) as usize;
            while !ptr::eq(curr, self) && curr.next[next_idx].is_null() {
                curr = unsafe { &*curr.fail };
            }
            if !curr.next[next_idx].is_null() {
                curr = unsafe { &*curr.next[next_idx] };
            }
            if curr.matched {
                return true;
            }
        }
        false
    }
}