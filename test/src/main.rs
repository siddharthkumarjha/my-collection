fn main() {
        let mut arr: [u32; 8] = [8, 9, 1, 10, 4, 5, 6, 19];
        let len = arr.len();
        for i in 0..len
        {
                for j in i..len
                {
                        if arr[i] > arr[j]
                        {
                                arr[i] = arr[i] ^ arr[j];
                                arr[j] = arr[i] ^ arr[j];
                                arr[i] = arr[i] ^ arr[j];
                        }
                }
        }

        for r in &arr
        {
                print!("{r} ");
        }
}
