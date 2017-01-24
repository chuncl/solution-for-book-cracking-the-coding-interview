// explain what the following code does n > 0 && (n & (n-1)) == 0
// power of 2. NOTE, original description in the book is not totally accurate n & (n-1) == 0, 
// - as n == 0 satisfy this condition but it is not power of 2
// - NOTE: bit operations can only be applied on integer or enum, not double/float...