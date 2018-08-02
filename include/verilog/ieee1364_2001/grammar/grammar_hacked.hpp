
#ifndef LIBVERILOG_IEEE1364_2001_GRAMMAR_GRAMMAR_HPP
#define LIBVERILOG_IEEE1364_2001_GRAMMAR_GRAMMAR_HPP

// #include <verilog/ieeel1364_2005/grammar/source_text.hpp>
// #include "./source_text.hpp"
// #include "./attribute.hpp"
#include "./base.hpp"
#include "./keywords.hpp"
#include "./commands.hpp"

namespace Verilog {
namespace IEEE1364_2001 {
namespace Grammar {
// clang-format off

struct sdf_annotate_task;

struct ignored;
struct ignored_content : 
  sor<
    qstring,
    plus<character>,
    plus_blank,
    // hierarchical_identifier,
    special_character_without_brackets,
    ignored
> {};

struct ignored : seq<
  star<ignored_content>
> {};

struct op_sep_ignored : plus<
  opt<sps>,
  tao::pegtl::list<ignored,opt<sps>>
> {};

struct unimplemented : if_must<
  open,
  star<ignored>,
  star<ignored_content>,
  star<ignored>,
  until<close>
> {};

struct unimplemented_brackets : if_must<
  seq<open>,
  star<bracket_contents>,
  star<bracket_pairs>,
  star<bracket_contents>,
  until<close>
> {};

struct begin_end_pair;
// struct begin_end_pairs;

struct begin_end_contents : 
  sor<
    qstring,
    separator,
    one<'`'>,
    plus<special_character>,
    // seq<blank,any_character,blank>,
    plus<not_at<sor<begin_keyword,end_keyword>>, any_character>,
    // hierarchical_identifier,
    begin_end_pair
> {};

struct begin_end_pair : if_must<
  begin_keyword,
  star<begin_end_contents>,
  end_keyword
> {};

// struct begin_end_pairs : plus<
//   opt<sps>,
//   tao::pegtl::list<begin_end_pair,opt<sps>>
// > {};

struct unimplemented_begin_end : if_must<
  begin_keyword,
  star<begin_end_contents>,
  // star<begin_end_pairs>,
  // star<begin_end_contents>,
  until<end_keyword>
> {};

// struct _module_item_ : sor<
//   op_sep_ignored,
//   until<eol>
// > {};



struct include_statement : seq< 
  include_keyword,
  seq<
    plus_blank,
    one<'"'>, 
    file_path_spec,
    one<'"'>
  >
>{};


struct compiler_directive : seq<
  one<'`'>, //one<'‘'>,
  sor<
    include_statement
  >
> {};


// struct net_declaration : seq<
//   net_keyword,
//   until<one<';'>>
// >{};
// struct reg_declaration : seq<
//   reg_keyword,
//   until<one<';'>>
// >{};
// struct integer_declaration : seq<
//   integer_keyword,
//   until<one<';'>>
// >{};
// struct real_declaration : seq<
//   real_keyword,
//   until<one<';'>>
// >{};
// struct time_declaration : seq<
//   time_keyword,
//   until<one<';'>>
// >{};
// struct realtime_declaration : seq<
//   realtime_keyword,
//   until<one<';'>>
// >{};
// struct event_declaration : seq<
//   event_keyword,
//   until<one<';'>>
// >{};
// struct genvar_declaration : seq<
//   genvar_keyword,
//   until<one<';'>>
// >{};
// struct task_declaration : seq<
//   task_keyword,
//   until<one<';'>>
// >{};
// struct function_declaration : seq<
//   function_keyword,
//   until<one<';'>>
// >{};

// struct module_or_generate_item_declaration : sor< 
//   net_declaration,
//   reg_declaration,
//   integer_declaration,
//   real_declaration,
//   time_declaration,
//   realtime_declaration,
//   event_declaration,
//   genvar_declaration,
//   task_declaration,
//   function_declaration
// > {};

struct module_instance_identifier : alias<identifier>{};

struct fake_bus_range : seq<
  one<'['>,
  until<one<']'>>
>{};

struct name_of_instance : seq < 
  module_instance_identifier, 
  opt<fake_bus_range>
>{};

struct module_instance : seq<
  name_of_instance, opt<separator>, seq<one<'('>, /*opt<list_of_port_connections>,*/ until<one<')'>>>
>{};

struct module_identifier : alias<identifier> {};

struct module_instantiation : seq<
  // opt< parameter_value_assignment> 
  module_identifier,
  plus_blank,
  list<module_instance, one<','>, separator>,
  // opt< list<module_instance, one<','> > >,
  opt<separator>,
  one<';'>
> {};

struct at_least_blank_separator : seq<
  opt<separator>,  
  plus_blank,
  opt<separator>
>{};

struct initial_block : seq < //causes parse errors when if_must
  initial_keyword,
  // at_least_blank_separator,
  separator,
  begin_keyword,
  star<
    until<
      sor<
        sdf_annotate_task,
        unimplemented_begin_end
      >
    >
  >,
  until<end_keyword>
> {};

struct _module_declaration_ : if_must<
  module_keyword,
  plus_blank,
  module_identifier,
  until<one<';'>>,
  opt<separator>,
  star<
    tao::pegtl::until<
      sor<
        // separator, 
        initial_block,
        module_instantiation
      >,
      seq<not_at<comment>, tao::pegtl::any>
    >
  >,
  until<endmodule_keyword>
> {};

struct _module_description_ : sor<
  _module_declaration_ //,
  // udp_declaration
> {};

struct _grammar_ : must<
  opt<separator>,
  opt<list<
    tao::pegtl::until<
      sor<separator, compiler_directive,_module_description_>, seq<not_at<comment>, tao::pegtl::any>
    >,
    opt<blank>
  >>,
  opt<separator>
  
  // opt<eof>
> {};

// clang-format on
} // namespace Grammar
} // namespace IEEE1364_2001
} // namespace Verilog

#endif // LIBVERILOG_IEEE1364_2001_GRAMMAR_GRAMMAR_HPP
