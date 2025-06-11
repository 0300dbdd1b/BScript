#include "include/script-interpreter.h"

const char *GetScriptStatusName(SCRIPT_STATUS status)
{
	static const char *scriptStatusNames[] = {
	"NOSTATUS",
	"SCRIPT_PENDING_EXECUTION",
	"SCRIPT_SUCCESS",
	"SCRIPT_SUCCESS_STACK_NOT_EMPTY",
	"SCRIPT_FAILURE",
	"SCRIPT_FAILURE_MISSING_SCRIPT_SEGMENT",
	"SCRIPT_FAILURE_DISABLED_OPCODE",
	"SCRIPT_FAILURE_STACK_OVERFLOW",
	"SCRIPT_FAILURE_STACK_UNDERFLOW",
	"SCRIPT_FAILURE_STACK_NOT_EMPTY"
	};
	return scriptStatusNames[status];
}

const char *GetErrorName(ERROR error)
{
	static const char *errorNames[] = {
		"NOERROR",
		"SCRIPT_MISSING_SEGMENT"
	};

	return errorNames[error];
}
