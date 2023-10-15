fn main() {
    const A_SIZE:usize = 100;
    let mut seive = [true; A_SIZE];

    seive[0] = false;
    seive[1] = false;

    let mut i = 2;
    while i < 10 {
        if seive[i] {
            let mut j = i * i;
            while j < A_SIZE {
                seive[j] = false;
                j += i
            }
        }
        i += 1;
    }
    let mut index = 0;
    for num in seive {
        if num {
            println!("{index}");
        }
        index += 1;
    }
}
