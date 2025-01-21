#include "include/ScriptInterpreter.h"
#include "include/opcodes.h"
#include "include/platform.h"
#include <string.h>


/* -------------------------- INTERPRETER --------------------------------- */

void InitInterpreter(ScriptInterpreter *env)
{
	env->executedByteCount			= 0;
	env->scriptExecutionStatus		= SCRIPT_NOSTATUS;
	env->mainStack.stackSize		= 0;
	env->altStack.stackSize			= 0;
}

void SetInterpreterScript(ScriptInterpreter *env, Script *script)
{
	env->script = *script;
	env->scriptExecutionStatus = SCRIPT_PENDING_EXECUTION;
}

SCRIPT_STATUS IsValid(ScriptInterpreter *env)
{
	if ((env->scriptExecutionStatus == SCRIPT_FAILURE) || (env->scriptExecutionStatus == SCRIPT_FAILURE_STACK_UNDERFLOW) ||
		(env->scriptExecutionStatus == SCRIPT_FAILURE_STACK_OVERFLOW) || (env->scriptExecutionStatus == SCRIPT_FAILURE_MISSING_SCRIPT_SEGMENT))
		return SCRIPT_FAILURE;
	else
		return SCRIPT_SUCCESS;
}


void ValidateScript(ScriptInterpreter *env)
{
	if ((env->scriptExecutionStatus != SCRIPT_NOSTATUS) && (env->scriptExecutionStatus != SCRIPT_PENDING_EXECUTION))
		return;

	U32 value;
	StackElement element = StackPop(&env->mainStack);
	StackPush(&env->mainStack, element);
	memcpy(&value, element.element, 4);
	if (value)
		env->scriptExecutionStatus = (env->mainStack.stackSize > 1) ? SCRIPT_SUCCESS_STACK_NOT_EMPTY : SCRIPT_SUCCESS;
	else
		env->scriptExecutionStatus = SCRIPT_FAILURE;
}

SCRIPT_STATUS ExecuteScript(ScriptInterpreter *env)
{
	while (env->scriptExecutionStatus == SCRIPT_PENDING_EXECUTION)
	{
		if (env->executedByteCount >= env->script.scriptSize)
			break;
		printf("executing Opcode : %s\n", GetOpcodeName(env->script.bytes[env->executedByteCount]));
		ExecuteOpcodes(env);
		PrintStacks(&env->mainStack, &env->altStack);
		printf("\n\n");
	}
	ValidateScript(env);
	return env->scriptExecutionStatus;
}
