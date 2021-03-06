#include "verilog/ieee1800_2012/actions/command_listener.hpp"
#include <string>

using namespace Verilog;
namespace rsv = ranges::view;

// namespace ac = antlrcpp;
// using sp = SV2012Parser;

CommandListener::CommandListener(std::shared_ptr<SV2012Parser> parser,
                                 std::shared_ptr<DesignReader> reader,
                                 std::string file_path) :
    parser_(parser),
    reader_(reader),
    file_path_(file_path)
{
}

void CommandListener::exitModule_declaration(
    SV2012Parser::Module_declarationContext *ctx)
{
  Parse::Util::debug_puts("DEBUG: CommandListener: Exit module declaration");
  reader_->next_module();
}

void CommandListener::exitSystem_tf_call(
    SV2012Parser::System_tf_callContext *ctx)
{

  // Parse::Util::debug_print
  auto tokens = parser_->getTokenStream();
  Parse::Util::debug_puts("DEBUG: CommandListener: Found system task/function");
  Parse::Util::debug_puts("DEBUG: CommandListener: Match ({})",
                          tokens->getText(ctx));

  if ((ctx->System_tf_identifier()) && (ctx->list_of_arguments())) {

    auto str = ctx->System_tf_identifier()->getSymbol()->getText();
    SV2012Parser::List_of_argumentsContext *args_ctx = ctx->list_of_arguments();
    Command command{};

    Parse::Util::debug_puts("DEBUG: CommandListener: identifier ({})", str);
    Parse::Util::debug_puts("DEBUG: CommandListener: args ({})",
                            tokens->getText(args_ctx));

    if (str == "$sdf_annotate") {
      Parse::Util::debug_puts(
          "DEBUG: CommandListener: detected $sdf_annotate system task");
      auto sdf_file_ctx = args_ctx->expression();

      if (!sdf_file_ctx) {
        throw std::runtime_error("ParseError : CommandListener: $sdf_annotate argument list empty.");
      }
      // std::cout << "-- detected hierarchical identifier" << std::endl;

      auto ctxv = args_ctx->positional_expression_argument();

      std::string sdf_file = tokens->getText(sdf_file_ctx);
      Parse::Util::debug_puts( 
          "DEBUG: CommandListener: $sdf_annotate system file path : ({})", sdf_file);
      //unwrap if quoted string
      sdf_file = sdf_file.substr(1,sdf_file.size()-2);
      Parse::Util::debug_puts( 
          "DEBUG: CommandListener: $sdf_annotate system file path : ({})", sdf_file);
      std::optional<std::string> name_of_instance{};
      std::optional<std::string> config_file{};
      std::optional<std::string> log_file{};
      std::optional<std::string> mtm_spec{};
      std::optional<std::string> scale_factors{};
      std::optional<std::string> scale_type{};

      if (!ctxv.empty()) {
        for (auto &&[i, op_ctx] : rsv::zip(rsv::indices, ctxv)) {
          switch (i) {
          case 0:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              name_of_instance = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;
          case 1:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              config_file = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;
          case 2:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              log_file = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;
          case 3:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              mtm_spec = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;
          case 4:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              scale_factors = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;
          case 5:
            if (op_ctx->expression()) {
              auto str = tokens->getText(op_ctx->expression());
              scale_type = (str.substr(0,1) =="\"") ? str.substr(1,str.size()-2) : str;
            }
            break;

          default:
            break;
          }
        }
      }
      Parse::Util::debug_puts(
          "DEBUG: CommandListener: build SDFAnnotateCommand");
      SDFAnnotateCommand sdf_annotate_command{
          sdf_file, 
          name_of_instance, 
          config_file, 
          log_file,
          mtm_spec, 
          scale_factors, 
          scale_type
        };

      command = sdf_annotate_command;
      reader_->command(command);
      Parse::Util::debug_puts("DEBUG: CommandListener: store command");
    } else {
      // do nothing
    }
  } else {
    Parse::Util::debug_puts("DEBUG : CommandListener: task/function ignored");
  }
}