enum CommonDataType {
    PduType([u8; 64]),
    SignalType(u64),
}
fn main() {
    let a: [u8; 64] = [0xff, 0xfd, 0xcc, 0xfc, 0xdd, ..0];
    let obj = CommonDataType::PduType(a);
}
