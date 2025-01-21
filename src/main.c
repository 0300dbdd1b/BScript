
#include "include/ScriptInterpreter.h"
#include "include/opcodes.h"

int main(int argc, char **argv)
{
	ScriptInterpreter *env 	= (ScriptInterpreter *)malloc(sizeof(ScriptInterpreter));
	Script *script	= (Script *)malloc(sizeof(Script));

	InitInterpreter(env);
	InitScript(script, "51515174515151");

	SetInterpreterScript(env, script);
	PrintScript(script);

	SCRIPT_STATUS status = ExecuteScript(env);
	printf("Script finished with code : %s\n", GetScriptStatusName(status));

	free(env);
	free(script);
}
