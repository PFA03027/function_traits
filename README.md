# function_traits
 Get traits of function object
 This traits class support below function type
  * Function pointer
  * Member function pointer
  * Functor( that class have function call operator. )

 This traits class is created for the type based switch function of std::any, std::variant, derived classes by dynamic cast.
 Type based switch idea come from https://www.modernescpp.com/index.php/visiting-a-std-variant-with-the-overload-pattern/
 