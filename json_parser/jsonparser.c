#include <stdio.h>
#include <stdlib.h>
#include <mpc.h>

int main(int argc, char** argv){

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* String= mpc_new("string");
  mpc_parser_t* Value= mpc_new("value");
  mpc_parser_t* Array= mpc_new("array");
  mpc_parser_t* Pair= mpc_new("pair");
  mpc_parser_t* Object= mpc_new("object");
  mpc_parser_t* Json= mpc_new("json");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number : /-?[0-9]+(\\.[0-9]+)?([eE][+-]?[0-9]+)?/ ;   \
      string : /\"(\\\\.|[^\"])*\"/ ;                         \
      value  : <number> | <string> | \"true\" | \"false\" |   \
               \"null\" | <object> | <array> ;                \
      array  : '[' <value> (',' <value>)* ']' ;                \
      pair   : <string> ':' <value> ;                         \
      object : '{' <pair> (',' <pair>)* '}' ;                  \
      json   : /^/ <value> /$/ ;                              \
    ",
  Number,String,Value,Array,Pair,Object,Json);
  
  char* input = NULL;
  size_t len = 0;
  printf("Enter JSON:");
  getline(&input,&len,stdin);

  mpc_result_t r;
  if (mpc_parse("<stdin>", input, Json, &r)) {
    printf("Valid JSON!\n");
    mpc_ast_delete(r.output);
  } else {
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
  free(input);
  mpc_cleanup(7, Number, String, Value, Array, Pair, Object, Json);
  
  return 0;
}
