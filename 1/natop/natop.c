#include "natop.h"
#include "natio.h"
#include <unistd.h>

nat sum(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (is_zero(x) || is_infty(y)) {
    return y;
  }
  return sum(pred(x), succ(y));
}

static nat dist_sub(nat x, nat y) {
  if (is_zero(x)) {
    return y;
  }
  if (is_zero(y)) {
    return x;
  }
  return dist_sub(pred(x), pred(y));
}

nat dist(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (is_zero(x) || is_infty(y)) {
    return y;
  }
  if (is_zero(y) || is_infty(x)) {
    return x;
  }
  return dist_sub(pred(x), pred(y));
}

nat min(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x) || is_zero(y)) {
    return y;
  }
  if (is_infty(y) || is_zero(x)) {
    return x;
  }
  return succ(min(pred(x), pred(y)));
}

nat max(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x) || is_zero(y)) {
    return x;
  }
  if (is_infty(y) || is_zero(x)) {
    return y;
  }
  return succ(max(pred(x), pred(y)));
}

static bool is_infeq(nat x, nat y) {
  if (is_zero(x)) {
    return is_zero(y);
  }
  if (is_zero(y)) {
    return false;
  }
  return is_infeq(pred(x), pred(y));
}

bool is_eq(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return is_infty(y);
  }
  if (is_infty(y)) {
    return false;
  }
  return is_infeq(x, y);
}

static bool is_infneq(nat x, nat y) {
  if (is_zero(x)) {
    return !is_zero(y);
  }
  if (is_zero(y)) {
    return true;
  }
  return is_infneq(pred(x), pred(y));
}

bool is_neq(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return !is_infty(y);
  }
  if (is_infty(y)) {
    return true;
  }
  return is_infneq(x, y);
}

static bool is_infleq(nat x, nat y) {
  if (is_zero(x)) {
    return true;
  }
  if (is_zero(y)) {
    return false;
  }
  return is_infleq(pred(x), pred(y));
}

bool is_leq(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return is_infty(y);
  }
  if (is_infty(y)) {
    return false;
  }
  return is_infleq(x, y);
}

static bool is_inflth(nat x, nat y) {
  if (is_zero(x)) {
    return !is_zero(y);
  }
  if (is_zero(y)) {
    return false;
  }
  return is_inflth(pred(x), pred(y));
}

bool is_lth(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x) || is_infty(y)) {
    return false;
  }
  return is_inflth(x, y);
}

static bool is_infgeq(nat x, nat y) {
  if (is_zero(x)) {
    return is_zero(y);
  }
  if (is_zero(y)) {
    return true;
  }
  return is_infeq(pred(x), pred(y));
}

bool is_geq(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return is_infty(y);
  }
  if (is_infty(y)) {
    return false;
  }
  return is_infgeq(x, y);
}

static bool is_infgth(nat x, nat y) {
  if (is_zero(x)) {
    return false;
  }
  if (is_zero(y)) {
    return true;
  }
  return is_infgth(pred(x), pred(y));
}

bool is_gth(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return !is_infty(y);
  }
  if (is_infty(y)) {
    return false;
  }
  return is_infgth(x, y);
}

static nat prod_sub(nat x, nat y, nat res) {
  if (is_zero(x) || is_infty(res)) {
    return res;
  }
  return prod_sub(pred(x), y, sum(res, y));
}

nat prod(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (is_zero(x)) {
    return is_infty(y) ? undef() : zero();
  }
  if (is_zero(y)) {
    return is_infty(x) ? undef() : zero();
  }
  return is_inflth(x, y) ? prod_sub(x, y, zero()) : prod_sub(y, x, zero());
}

static nat quot_sub(nat x, nat y) {
  if (is_inflth(x, y)) {
    return zero();
  }
  return succ(quot_sub(sub(x, y), y));
}

nat quot(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_zero(y)) {
    if (is_zero(x)) {
      return undef();
    }
    return infty();
  }
  if (is_infty(y)) {
    if (is_infty(x)) {
      return undef();
    }
    return zero();
  }
  if (is_infty(x)) {
    return infty();
  }
  return quot_sub(x, y);
}

static nat sub(nat x, nat y) {
  if (is_zero(y)) {
    return x;
  }
  return sub(pred(x), pred(y));
}

static nat rem_sub(nat x, nat y) {
  if (is_inflth(x, y)) {
    return x;
  }
  return rem_sub(sub(x, y), y);
}

nat rem(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x) || is_zero(y)) {
    return undef();
  }
  if (is_infty(y)) {
    return x;
  }
  return rem_sub(x, y);
}
