pub mod matrix;

#[cfg(test)]
mod tests {
    use crate::matrix::test;
    #[test]
    fn it_works() {
        assert_eq!(2, test());
    }
}
