fn main() {
    let scan = &mut Scanner::default();
    let n: usize = scan.next();
    let k: usize = scan.next();
    
    let mut arr: Vec<i32> = (0..n).map(|_| scan.next()).collect();
    let mut history: Vec<i32> = vec![];
    merge_sort(&mut history, &mut arr, 0, n-1);

    if let Some(val) = history.get(k-1) {
        println!("{val}");
    } else {
        println!("-1");
    }
}

fn merge_sort(history: &mut Vec<i32>, arr: &mut [i32], p: usize, q: usize) {
    if p < q {
        let m = (p + q) / 2;
        merge_sort(history, arr, p, m);
        merge_sort(history, arr, m+1, q);
        merge(history, arr, p, m, q);
    }
}

fn merge(history: &mut Vec<i32>, arr: &mut [i32], p: usize, q: usize, r: usize) {
    let mut tmp: Vec<i32> = vec![0; r-p+1];
    let mut i = p;
    let mut j = q+1;
    let mut t = 0;

    while i <= q && j <= r {
        if arr[i] <= arr[j] {
            tmp[t] = arr[i];
            t += 1;
            i += 1;
        } else {
            tmp[t] = arr[j];
            t += 1;
            j += 1;
        }
    }
    while i <= q {
        tmp[t] = arr[i];
        t += 1;
        i += 1;
    }
    while j <= r {
        tmp[t] = arr[j];
        t += 1;
        j += 1;
    }

    for i in 0..tmp.len() {
        history.push(tmp[i].clone());
        arr[p+i] = tmp[i];
    }
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}
impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}