struct Obj {
  Obj& operator=(const Obj& other) {
    this->val = other.val;
    return *this; // GOOD (common case)
  }
  
private:
  int val;
};

class Container {
  /* NB: Has generated operator= */
  Obj m_x;
  Obj m_y;
};

struct Bad1 {
  Bad1& operator=(const Bad1& other) {
    return const_cast<Bad1&>(other); // BAD (does not return a reference to *this)
  }
};

struct Bad2 {
  Bad2 operator=(const Bad2& other) {
    return *this; // BAD (return type is not a reference)
  }
};

struct External {
  External& operator=(const External& other); // GOOD (assume correct)
};

class ReturnAssignment {
public:
  ReturnAssignment(int _val) : val(_val) {}

  ReturnAssignment &operator=(const ReturnAssignment &other) {
    this->val = other.val;
    return *this; // GOOD
  }

  ReturnAssignment &operator=(int _val) {
    return *this = ReturnAssignment(_val); // GOOD (calls above `operator=`)
  }

  int val;
};

template<class T>
class TemplateReturnAssignment {
public:
  TemplateReturnAssignment(T _val) : val(_val) {}

  TemplateReturnAssignment &operator=(const TemplateReturnAssignment &other) {
    this->val = other.val;
    return *this; // GOOD
  }

  TemplateReturnAssignment &operator=(T _val) {
    return *this = TemplateReturnAssignment(_val); // GOOD (calls above `operator=`)
  }

  TemplateReturnAssignment &operator=(bool b) {
    return *(new TemplateReturnAssignment(0)); // BAD (does not return a reference to *this)
  }

  T val;
};

class ReturnBuiltInAssign {
public:
  ReturnBuiltInAssign(int _val) : val(_val) {}

  ReturnBuiltInAssign &operator=(int _val) {
    return *this = ReturnBuiltInAssign(_val); // GOOD (uses built-in `AssignExpr`)
  }

  int val;
};

class Obj2 {
public:
  Obj2 &getThis() {
    return *this;
  }

  Obj2 *getThisPtr() {
    return this;
  }

  Obj2 &operator=(int _val) {
    val = _val;
    return getThis(); // GOOD (returns *this)
  }

  Obj2 &operator=(int *_val) {
    val = *_val;
    return this->getThis(); // GOOD (returns *this)
  }

  Obj2 &operator=(int **_val) {
    val = **_val;
    return (getThis()); // GOOD (returns *this)
  }

  Obj2 &operator=(int ***_val) {
    val = ***_val;
    return *(this->getThisPtr()); // GOOD (returns *this)
  }

private:
  int val;
};

struct Exception {
  virtual ~Exception();
};

class AlwaysThrows {
public:
  AlwaysThrows &operator=(int _val) { // GOOD (always throws)
    throw Exception();
    // No `return` statement is generated by the C++ front end because it can
    // statically see that the end of the function is unreachable.
  }

  AlwaysThrows &operator=(int *_val) { // GOOD (always throws)
    int one = 1;
    if (one)
      throw Exception();
    // A `return` statement is generated by the C++ front end, but the
    // control-flow pruning in QL will establish that this is unreachable.
  }
};

class Reachability {
  Reachability &operator=(Reachability &that) { // GOOD
    int one = 1;
    if (one)
      return *this;
    else
      return that; // unreachable
  }

  // helper function that always returns a reference to `*this`.
  Reachability &returnThisReference() {
    int one = 1;
    if (one)
      return *this;
    else
      return staticInstance; // unreachable
  }

  // helper function that always returns `this`.
  Reachability *const returnThisPointer() {
    int one = 1;
    if (one)
      return this;
    else
      return &staticInstance; // unreachable
  }

  Reachability &operator=(int _val) { // GOOD
    return returnThisReference();
  }

  Reachability &operator=(short _val) { // GOOD
    return *returnThisPointer();
  }

  static Reachability staticInstance;
};

class Forgivable {
  // GOOD: wrong return type but that doesn't matter on a deleted function.
  Forgivable operator=(const Forgivable &_val) = delete;

private:
  // GOOD: wrong return type but that doesn't matter because this operator is
  // private and probably also unimplemented, so no code can call it.
  Forgivable operator=(int *_val);
};

int main() {
  Container c;
  c = c;
  TemplateReturnAssignment<int> tra(1);
  tra = 2;
  tra = true;
  return 0;
}
