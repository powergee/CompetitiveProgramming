use std::{
    io::{stdin, BufRead},
    iter::once,
};

fn main() {
    let (s, n, k, r1, r2, c1, c2) = {
        let buf = &mut String::new();
        stdin().lock().read_line(buf).unwrap();
        let mut iter = buf.trim().split_ascii_whitespace();
        let mut read = || iter.next().unwrap().parse::<usize>().unwrap();
        (read(), read(), read(), read(), read(), read(), read())
    };

    let size = n.pow(s as u32);
    let mut canvas = vec![vec![false]];
    let mut cell_size = size;
    let mut start = (0, 0);
    while cell_size > 1 {
        let mut next_canvas = vec![vec![false; n * canvas[0].len()]; n * canvas.len()];
        for i in 0..canvas.len() {
            for j in 0..canvas[0].len() {
                if canvas[i][j] {
                    for ni in n * i..n * (i + 1) {
                        for nj in n * j..n * (j + 1) {
                            next_canvas[ni][nj] = true;
                        }
                    }
                } else {
                    let nis = n * i + (n - k) / 2;
                    let njs = n * j + (n - k) / 2;
                    for ni in nis..nis + k {
                        for nj in njs..njs + k {
                            next_canvas[ni][nj] = true;
                        }
                    }
                }
            }
        }
        cell_size /= n;
        let crop_start = ((r1 - start.0) / cell_size, (c1 - start.1) / cell_size);
        let crop_end = ((r2 - start.0) / cell_size, (c2 - start.1) / cell_size);
        start = (r1 / cell_size * cell_size, c1 / cell_size * cell_size);
        canvas = next_canvas
            .into_iter()
            .skip(crop_start.0)
            .take(crop_end.0 - crop_start.0 + 1)
            .map(|row| {
                row.into_iter()
                    .skip(crop_start.1)
                    .take(crop_end.1 - crop_start.1 + 1)
                    .collect()
            })
            .collect();
    }

    print!(
        "{}",
        canvas
            .into_iter()
            .map(|row| row
                .into_iter()
                .map(|cell| if cell { '1' } else { '0' })
                .chain(once('\n')))
            .flatten()
            .collect::<String>()
    )
}
