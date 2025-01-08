fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn main() {
    let string1 = String::from("string");
    let string2 = "Short";

    let res = longest(&string1, &string2);
    println!("The longest string is {}", res);
}
