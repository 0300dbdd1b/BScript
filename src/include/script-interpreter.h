#ifndef _SCRIPT_INTERPRETER_H
#define _SCRIPT_INTERPRETER_H

#include "platform.h"

	#ifndef		MAX_STACK_SIZE
		#define MAX_STACK_SIZE			1000
	#endif

	#ifndef		MAX_STACK_ITEMS
		#define MAX_STACK_ITEMS			1500
	#endif

	#ifndef		MAX_SCRIPT_SIZE
		#define MAX_SCRIPT_SIZE			10000
	#endif


	#ifndef		MAX_STACK_ELEMENT_SIZE 
		#define MAX_STACK_ELEMENT_SIZE	520
	#endif

/* --------------------------------- STACK ------------------------------------ */
typedef struct StackElement
{
	U8		element[MAX_STACK_ELEMENT_SIZE];
	size_t	elementSize;
} StackElement;

typedef struct Stack
{
	StackElement	elements[MAX_STACK_ITEMS];
	size_t			stackSize;
} Stack;
void StackPush(Stack  *stack, StackElement element);
StackElement StackPop(Stack *stack);
void PrintStackElement(StackElement *element);
void PrintStack(Stack *stack);
void PrintStacks(Stack *mainStack, Stack *altStack);

/* --------------------------------- SCRIPT ------------------------------------ */
#define STANDARD	1
#define NONSTANDARD	0
typedef enum SCRIPT_STATUS : U8
{
	SCRIPT_NOSTATUS,
	SCRIPT_PENDING_EXECUTION,
	SCRIPT_SUCCESS,
	SCRIPT_SUCCESS_STACK_NOT_EMPTY,
	SCRIPT_FAILURE,
	SCRIPT_FAILURE_MISSING_SCRIPT_SEGMENT,
	SCRIPT_FAILURE_DISABLED_OPCODE,
	SCRIPT_FAILURE_STACK_OVERFLOW,
	SCRIPT_FAILURE_STACK_UNDERFLOW,
	SCRIPT_FAILURE_STACK_NOT_EMPTY
} SCRIPT_STATUS;
const char *GetScriptStatusName(SCRIPT_STATUS status);

typedef struct Script
{
	U8				bytes[MAX_SCRIPT_SIZE];
	size_t			scriptSize;
	char			hex[MAX_SCRIPT_SIZE * 2];
} Script;

void InitScript(Script *script, const char *rawScript);
void PrintScript(Script *script);

typedef struct ScriptInterpreter
{
	Script			script;
	SCRIPT_STATUS	scriptExecutionStatus;
	Stack			mainStack;
	Stack			altStack;
	size_t			sigopCount;
	size_t			executedOpcodeCount;
	size_t			stackItemPushedCount;
	size_t			executedByteCount;
} ScriptInterpreter;

void InitInterpreter(ScriptInterpreter *env);
void SetInterpreterScript(ScriptInterpreter *env, Script *script);
SCRIPT_STATUS ExecuteScript(ScriptInterpreter *env);


typedef enum ERROR : U16
{
	NOERROR,
	SCRIPT_MISSING_SEGMENT,
} ERROR;

const char *GetErrorName(ERROR error);


// FIXME: Might want to move utils functions to a specific header
void ExecuteOpcodes(ScriptInterpreter *env);
void hexStringToBytes(const char *hexString, uint8_t *byteArray, size_t arraySize, size_t *outLength);
void ExecutePushDataOpcodes(ScriptInterpreter *env);
void ModifyBytes(U8 bytes[], size_t size, int value, U8 isBigEndian);
U8 IsHex(const char *str);

#endif // !_SCRIPT_INTERPRETER_H
