const op_t OP_NOP = 0;
const op_t OP_RETURN = 1;
const op_t OP_PUSH = 2;
const op_t OP_POP = 3;
const op_t OP_CALL = 4;
const op_t OP_LOAD_FREE = 5;
const op_t OP_SAVE_FREE = 6;
const op_t OP_LOAD_CAPTURED = 7;
const op_t OP_SAVE_CAPTURED = 8;
const op_t OP_SAVE = 9;
const op_t OP_DCOLON = 10;
const op_t OP_SUBSASGN = 11;
const op_t OP_LOAD_CONST = 12;
const op_t OP_LOAD = 13;
const op_t OP_START_LIST = 14;
const op_t OP_END_LIST = 15;
const op_t OP_LOAD_STACK = 16;
const op_t OP_SUBSREF = 17;
const op_t OP_COLON = 18;
const op_t OP_ADD = 19;
const op_t OP_MINUS = 20;
const op_t OP_MTIMES = 21;
const op_t OP_MRDIVIDE = 22;
const op_t OP_MLDIVIDE = 23;
const op_t OP_OR = 24;
const op_t OP_AND = 25;
const op_t OP_LT = 26;
const op_t OP_LE = 27;
const op_t OP_GT = 28;
const op_t OP_GE = 29;
const op_t OP_EQ = 30;
const op_t OP_NE = 31;
const op_t OP_TIMES = 32;
const op_t OP_RDIVIDE = 33;
const op_t OP_CASE = 34;
const op_t OP_COLUMN = 35;
const op_t OP_LDIVIDE = 36;
const op_t OP_NUMCOLS = 37;
const op_t OP_NEG = 38;
const op_t OP_PLUS = 39;
const op_t OP_NOT = 40;
const op_t OP_POWER = 41;
const op_t OP_DOTPOWER = 42;
const op_t OP_HERMITIAN = 43;
const op_t OP_TRANSPOSE = 44;
const op_t OP_INCR = 45;
const op_t OP_LHSCOUNT = 46;
const op_t OP_SUBSASGNM = 47;
const op_t OP_ZERO = 48;
const op_t OP_CELLROWDEF = 49;
const op_t OP_HCAT = 50;
const op_t OP_VCAT = 51;
const op_t OP_LOAD_GLOBAL = 52;
const op_t OP_LOAD_PERSIST = 53;
const op_t OP_LOAD_DYNAMIC = 54;
const op_t OP_SAVE_GLOBAL = 55;
const op_t OP_SAVE_DYNAMIC = 56;
const op_t OP_SAVE_PERSIST = 57;
const op_t OP_JUMP_ZERO = 58;
const op_t OP_JUMP = 59;
const op_t OP_TRY_BEGIN = 60;
const op_t OP_TRY_END = 61;
const op_t OP_THROW = 62;
const op_t OP_PRINT = 63;
const op_t OP_DEREF = 64;
const op_t OP_SUBSASGN_GLOBAL = 65;
const op_t OP_SUBSASGN_PERSIST = 66;
const op_t OP_SUBSASGN_CAPTURED = 67;
const op_t OP_SUBSASGN_FREE = 68;
const op_t OP_SUBSASGN_DYNAMIC = 69;
const op_t OP_LOOPCOUNT = 70;
