#include "include/script-interpreter.h"
#include "include/opcodes.h"

#include <string.h>

/* ----------------------------------------- OPCODES ------------------------------------------------------- */
static const char *opcodeStrings[] = {
		"OP_0",                // 0x00
		"OP_PUSHBYTES_1",      // 0x01
		"OP_PUSHBYTES_2",      // 0x02
		"OP_PUSHBYTES_3",      // 0x03
		"OP_PUSHBYTES_4",      // 0x04
		"OP_PUSHBYTES_5",      // 0x05
		"OP_PUSHBYTES_6",      // 0x06
		"OP_PUSHBYTES_7",      // 0x07
		"OP_PUSHBYTES_8",      // 0x08
		"OP_PUSHBYTES_9",      // 0x09
		"OP_PUSHBYTES_10",     // 0x0A
		"OP_PUSHBYTES_11",     // 0x0B
		"OP_PUSHBYTES_12",     // 0x0C
		"OP_PUSHBYTES_13",     // 0x0D
		"OP_PUSHBYTES_14",     // 0x0E
		"OP_PUSHBYTES_15",     // 0x0F
		"OP_PUSHBYTES_16",     // 0x10
		"OP_PUSHBYTES_17",     // 0x11
		"OP_PUSHBYTES_18",     // 0x12
		"OP_PUSHBYTES_19",     // 0x13
		"OP_PUSHBYTES_20",     // 0x14
		"OP_PUSHBYTES_21",     // 0x15
		"OP_PUSHBYTES_22",     // 0x16
		"OP_PUSHBYTES_23",     // 0x17
		"OP_PUSHBYTES_24",     // 0x18
		"OP_PUSHBYTES_25",     // 0x19
		"OP_PUSHBYTES_26",     // 0x1A
		"OP_PUSHBYTES_27",     // 0x1B
		"OP_PUSHBYTES_28",     // 0x1C
		"OP_PUSHBYTES_29",     // 0x1D
		"OP_PUSHBYTES_30",     // 0x1E
		"OP_PUSHBYTES_31",     // 0x1F
		"OP_PUSHBYTES_32",     // 0x20
		"OP_PUSHBYTES_33",     // 0x21
		"OP_PUSHBYTES_34",     // 0x22
		"OP_PUSHBYTES_35",     // 0x23
		"OP_PUSHBYTES_36",     // 0x24
		"OP_PUSHBYTES_37",     // 0x25
		"OP_PUSHBYTES_38",     // 0x26
		"OP_PUSHBYTES_39",     // 0x27
		"OP_PUSHBYTES_40",     // 0x28
		"OP_PUSHBYTES_41",     // 0x29
		"OP_PUSHBYTES_42",     // 0x2A
		"OP_PUSHBYTES_43",     // 0x2B
		"OP_PUSHBYTES_44",     // 0x2C
		"OP_PUSHBYTES_45",     // 0x2D
		"OP_PUSHBYTES_46",     // 0x2E
		"OP_PUSHBYTES_47",     // 0x2F
		"OP_PUSHBYTES_48",     // 0x30
		"OP_PUSHBYTES_49",     // 0x31
		"OP_PUSHBYTES_50",     // 0x32
		"OP_PUSHBYTES_51",     // 0x33
		"OP_PUSHBYTES_52",     // 0x34
		"OP_PUSHBYTES_53",     // 0x35
		"OP_PUSHBYTES_54",     // 0x36
		"OP_PUSHBYTES_55",     // 0x37
		"OP_PUSHBYTES_56",     // 0x38
		"OP_PUSHBYTES_57",     // 0x39
		"OP_PUSHBYTES_58",     // 0x3A
		"OP_PUSHBYTES_59",     // 0x3B
		"OP_PUSHBYTES_60",     // 0x3C
		"OP_PUSHBYTES_61",     // 0x3D
		"OP_PUSHBYTES_62",     // 0x3E
		"OP_PUSHBYTES_63",     // 0x3F
		"OP_PUSHBYTES_64",     // 0x40
		"OP_PUSHBYTES_65",     // 0x41
		"OP_PUSHBYTES_66",     // 0x42
		"OP_PUSHBYTES_67",     // 0x43
		"OP_PUSHBYTES_68",     // 0x44
		"OP_PUSHBYTES_69",     // 0x45
		"OP_PUSHBYTES_70",     // 0x46
		"OP_PUSHBYTES_71",     // 0x47
		"OP_PUSHBYTES_72",     // 0x48
		"OP_PUSHBYTES_73",     // 0x49
		"OP_PUSHBYTES_74",     // 0x4A
		"OP_PUSHBYTES_75",     // 0x4B
		"OP_PUSHDATA1",        // 0x4C
		"OP_PUSHDATA2",        // 0x4D
		"OP_PUSHDATA4",        // 0x4E
		"OP_1NEGATE",          // 0x4F
		"OP_RESERVED",         // 0x50
		"OP_1",                // 0x51
		"OP_2",                // 0x52
		"OP_3",                // 0x53
		"OP_4",                // 0x54
		"OP_5",                // 0x55
		"OP_6",                // 0x56
		"OP_7",                // 0x57
		"OP_8",                // 0x58
		"OP_9",                // 0x59
		"OP_10",               // 0x5A
		"OP_11",               // 0x5B
		"OP_12",               // 0x5C
		"OP_13",               // 0x5D
		"OP_14",               // 0x5E
		"OP_15",               // 0x5F
		"OP_16",               // 0x60
		"OP_NOP",              // 0x61
		"OP_VER",              // 0x62
		"OP_IF",               // 0x63
		"OP_NOTIF",            // 0x64
		"OP_VERIF",            // 0x65
		"OP_VERNOTIF",         // 0x66
		"OP_ELSE",             // 0x67
		"OP_ENDIF",            // 0x68
		"OP_VERIFY",           // 0x69
		"OP_RETURN",           // 0x6A
		"OP_TOALTSTACK",       // 0x6B
		"OP_FROMALTSTACK",     // 0x6C
		"OP_2DROP",            // 0x6D
		"OP_2DUP",             // 0x6E
		"OP_3DUP",             // 0x6F
		"OP_2OVER",            // 0x70
		"OP_2ROT",             // 0x71
		"OP_2SWAP",            // 0x72
		"OP_IFDUP",            // 0x73
		"OP_DEPTH",            // 0x74
		"OP_DROP",             // 0x75
		"OP_DUP",              // 0x76
		"OP_NIP",              // 0x77
		"OP_OVER",             // 0x78
		"OP_PICK",             // 0x79
		"OP_ROLL",             // 0x7A
		"OP_ROT",              // 0x7B
		"OP_SWAP",             // 0x7C
		"OP_TUCK",             // 0x7D
		"OP_CAT",              // 0x7E
		"OP_SUBSTR",           // 0x7F
		"OP_LEFT",             // 0x80
		"OP_RIGHT",            // 0x81
		"OP_SIZE",             // 0x82
		"OP_INVERT",           // 0x83
		"OP_AND",              // 0x84
		"OP_OR",               // 0x85
		"OP_XOR",              // 0x86
		"OP_EQUAL",            // 0x87
		"OP_EQUALVERIFY",      // 0x88
		"OP_RESERVED1",        // 0x89
		"OP_RESERVED2",        // 0x8A
		"OP_1ADD",             // 0x8B
		"OP_1SUB",             // 0x8C
		"OP_2MUL",             // 0x8D
		"OP_2DIV",             // 0x8E
		"OP_NEGATE",           // 0x8F
		"OP_ABS",              // 0x90
		"OP_NOT",              // 0x91
		"OP_0NOTEQUAL",        // 0x92
		"OP_ADD",              // 0x93
		"OP_SUB",              // 0x94
		"OP_MUL",              // 0x95
		"OP_DIV",              // 0x96
		"OP_MOD",              // 0x97
		"OP_LSHIFT",           // 0x98
		"OP_RSHIFT",           // 0x99
		"OP_BOOLAND",          // 0x9A
		"OP_BOOLOR",           // 0x9B
		"OP_NUMEQUAL",         // 0x9C
		"OP_NUMEQUALVERIFY",   // 0x9D
		"OP_NUMNOTEQUAL",      // 0x9E
		"OP_LESSTHAN",         // 0x9F
		"OP_GREATERTHAN",      // 0xA0
		"OP_LESSTHANOREQUAL",  // 0xA1
		"OP_GREATERTHANOREQUAL", // 0xA2
		"OP_MIN",              // 0xA3
		"OP_MAX",              // 0xA4
		"OP_WITHIN",           // 0xA5
		"OP_RIPEMD160",        // 0xA6
		"OP_SHA1",             // 0xA7
		"OP_SHA256",           // 0xA8
		"OP_HASH160",          // 0xA9
		"OP_HASH256",          // 0xAA
		"OP_CODESEPARATOR",    // 0xAB
		"OP_CHECKSIG",         // 0xAC
		"OP_CHECKSIGVERIFY",   // 0xAD
		"OP_CHECKMULTISIG",    // 0xAE
		"OP_CHECKMULTISIGVERIFY", // 0xAF
		"OP_NOP1",             // 0xB0
		"OP_CHECKLOCKTIMEVERIFY", // 0xB1
		"OP_CHECKSEQUENCEVERIFY", // 0xB2
		"OP_NOP4",             // 0xB3
		"OP_NOP5",             // 0xB4
		"OP_NOP6",             // 0xB5
		"OP_NOP7",             // 0xB6
		"OP_NOP8",             // 0xB7
		"OP_NOP9",             // 0xB8
		"OP_NOP10",            // 0xB9
		"OP_CHECKSIGADD",      // 0xBA
		"OP_RETURN_187",       // 0xBB
		"OP_RETURN_188",       // 0xBC
		"OP_RETURN_189",       // 0xBD
		"OP_RETURN_190",       // 0xBE
		"OP_RETURN_191",       // 0xBF
		"OP_RETURN_192",       // 0xC0
		"OP_RETURN_193",       // 0xC1
		"OP_RETURN_194",       // 0xC2
		"OP_RETURN_195",       // 0xC3
		"OP_RETURN_196",       // 0xC4
		"OP_RETURN_197",       // 0xC5
		"OP_RETURN_198",       // 0xC6
		"OP_RETURN_199",       // 0xC7
		"OP_RETURN_200",       // 0xC8
		"OP_RETURN_201",       // 0xC9
		"OP_RETURN_202",       // 0xCA
		"OP_RETURN_203",       // 0xCB
		"OP_RETURN_204",       // 0xCC
		"OP_RETURN_205",       // 0xCD
		"OP_RETURN_206",       // 0xCE
		"OP_RETURN_207",       // 0xCF
		"OP_RETURN_208",       // 0xD0
		"OP_RETURN_209",       // 0xD1
		"OP_RETURN_210",       // 0xD2
		"OP_RETURN_211",       // 0xD3
		"OP_RETURN_212",       // 0xD4
		"OP_RETURN_213",       // 0xD5
		"OP_RETURN_214",       // 0xD6
		"OP_RETURN_215",       // 0xD7
		"OP_RETURN_216",       // 0xD8
		"OP_RETURN_217",       // 0xD9
		"OP_RETURN_218",       // 0xDA
		"OP_RETURN_219",       // 0xDB
		"OP_RETURN_220",       // 0xDC
		"OP_RETURN_221",       // 0xDD
		"OP_RETURN_222",       // 0xDE
		"OP_RETURN_223",       // 0xDF
		"OP_RETURN_224",       // 0xE0
		"OP_RETURN_225",       // 0xE1
		"OP_RETURN_226",       // 0xE2
		"OP_RETURN_227",       // 0xE3
		"OP_RETURN_228",       // 0xE4
		"OP_RETURN_229",       // 0xE5
		"OP_RETURN_230",       // 0xE6
		"OP_RETURN_231",       // 0xE7
		"OP_RETURN_232",       // 0xE8
		"OP_RETURN_233",       // 0xE9
		"OP_RETURN_234",       // 0xEA
		"OP_RETURN_235",       // 0xEB
		"OP_RETURN_236",       // 0xEC
		"OP_RETURN_237",       // 0xED
		"OP_RETURN_238",       // 0xEE
		"OP_RETURN_239",       // 0xEF
		"OP_RETURN_240",       // 0xF0
		"OP_RETURN_241",       // 0xF1
		"OP_RETURN_242",       // 0xF2
		"OP_RETURN_243",       // 0xF3
		"OP_RETURN_244",       // 0xF4
		"OP_RETURN_245",       // 0xF5
		"OP_RETURN_246",       // 0xF6
		"OP_RETURN_247",       // 0xF7
		"OP_RETURN_248",       // 0xF8
		"OP_RETURN_249",       // 0xF9
		"OP_RETURN_250",       // 0xFA
		"OP_RETURN_251",       // 0xFB
		"OP_RETURN_252",       // 0xFC
		"OP_RETURN_253",       // 0xFD
		"OP_RETURN_254",       // 0xFE
		"OP_INVALIDOPCODE",    // 0xFF
		NULL
	};

OPCODE GetOpcode(const char *opcode)
{
	for (size_t i = 0; opcodeStrings[i] != NULL; i++)
	{
		if (strcmp(opcode, opcodeStrings[i]) == 0)
			return i;
	}
	return OP_INVALIDOPCODE;
}

const char *GetOpcodeName(OPCODE opcode)
{
	if (opcode <= OP_INVALIDOPCODE)
		return opcodeStrings[opcode];
	else
		return "UNKNOW_OPCODE";
}


/* ----------------------------------------- OP_PUSH ------------------------------------------------------- */
void OpPushData(ScriptInterpreter *env);
void OpPushBytes(ScriptInterpreter *env, U8 byteCount)
{
	StackElement element = {0}; if ((env->executedByteCount + byteCount + 1) > env->script.scriptSize)
	{
		printf("Error: Missing script segment\n");
		env->scriptExecutionStatus 	= SCRIPT_FAILURE_MISSING_SCRIPT_SEGMENT;
		return;
	}
	env->executedByteCount++;
	memcpy(&element.element, &env->script.bytes[env->executedByteCount], byteCount);
	element.elementSize = byteCount;
	StackPush(&env->mainStack, element);
	env->executedByteCount += byteCount;
	env->stackItemPushedCount++;
}

void OpPushNumber(ScriptInterpreter *env, U8 number)
{
    StackElement element = {0};
	element.element[0] = number;
	element.elementSize = 1;
    StackPush(&env->mainStack, element);
    env->executedByteCount++;
	env->stackItemPushedCount++;
}
void ExecutePushDataOpcodes(ScriptInterpreter *env) {
    if (env->executedByteCount > env->script.scriptSize)
		printf("Error\n");
	U8 opcode = env->script.bytes[env->executedByteCount];
	if (opcode == OP_0)
		OpPushNumber(env, 0);
	if ((OP_1 <= opcode) && (opcode <= OP_16))
		OpPushNumber(env, opcode - 0x50);
	else if ((OP_PUSHBYTES_1 <= opcode) && (opcode <= OP_PUSHBYTES_75))
		OpPushBytes(env, opcode);
	else
		printf("Unsupported Opcode : %02X\n", opcode);
}

/* ----------------------------------------- GENERAL OPCODES ------------------------------------------------------- */
void OpBooleanOperations(ScriptInterpreter *env)
{
	U8 opcode = env->script.bytes[env->executedByteCount];
	StackElement firstElement = StackPop(&env->mainStack);
	StackElement secondElement = StackPop(&env->mainStack);
	if ((firstElement.elementSize > 4) || (secondElement.elementSize > 4))
	{
		env->scriptExecutionStatus = SCRIPT_FAILURE;
		return;
	}
	U32 firstItem;
	U32 secondItem;
	memcpy(&firstItem, firstElement.element, 4);
	memcpy(&secondItem, secondElement.element, 4);
	env->executedByteCount++;
	if 		(opcode == OP_BOOLOR)
		OpPushNumber(env, (firstItem || secondItem) ? 1 : 0);
	else if	(opcode == OP_BOOLAND)
		OpPushNumber(env, (firstItem && secondItem) ? 1 : 0);
}

void ExecuteMathopcodes(ScriptInterpreter *env)
{
	if (env->executedByteCount >= env->script.scriptSize)
		printf("Error\n");
	U8 opcode = env->script.bytes[env->executedByteCount];
	if (opcode == OP_1ADD) // WARN: Check Endianness -- Must check for negative numbers.
	{
		StackElement element = StackPop(&env->mainStack);
		ModifyBytes(element.element, sizeof(element.element), 1, 0);
		StackPush(&env->mainStack, element);
		env->executedByteCount++;
	}
	else if (opcode == OP_1SUB)
	{
		StackElement element = StackPop(&env->mainStack);
		ModifyBytes(element.element, sizeof(element.element), -1, 0);
		StackPush(&env->mainStack, element);
		env->executedByteCount++;
	}
	else if ((opcode == OP_BOOLOR) || (opcode == OP_BOOLAND))
		OpBooleanOperations(env);
	else
		printf("Unsupported opcode\n");
}

/* ----------------------------------------- SINGLE OPCODES ------------------------------------------------------- */

void OpToAltStack(ScriptInterpreter *env)
{
	StackElement element = StackPop(&env->mainStack);
	StackPush(&env->altStack, element);
	env->executedByteCount++;
}

void OpFromAltStack(ScriptInterpreter *env)
{
	StackElement element = StackPop(&env->altStack);
	StackPush(&env->mainStack, element);
	env->executedByteCount++;
}


void OpEqual(ScriptInterpreter *env)
{
	StackElement element;
	if (env->mainStack.stackSize < 2)
	{
		env->scriptExecutionStatus = SCRIPT_FAILURE;
		return;
	}
	StackElement firstElement = StackPop(&env->mainStack);
	StackElement secondElement = StackPop(&env->mainStack);
	if (firstElement.elementSize == secondElement.elementSize)
	{
		if (memcmp(firstElement.element, secondElement.element, firstElement.elementSize) == 0)
		{
			OpPushNumber(env, 1);
			return;
		}
	}
	OpPushNumber(env, 0);
}

void OpVerify(ScriptInterpreter *env)
{
	if (env->mainStack.stackSize == 0)
	{
		env->scriptExecutionStatus = SCRIPT_FAILURE_STACK_UNDERFLOW;
		return;
	}
	U32 num = 0;
	StackElement element = StackPop(&env->mainStack);
	memcpy(&num, element.element, 4);
	env->executedByteCount++;
	printf("NUM: %d\n", num);
	if (num == 0)
		env->scriptExecutionStatus = SCRIPT_FAILURE;
}

void OpDrop(ScriptInterpreter *env)
{
	if (env->mainStack.stackSize == 0)
	{
		env->scriptExecutionStatus = SCRIPT_FAILURE_STACK_OVERFLOW;
		env->executedByteCount++;
		return;
	}
	StackPop(&env->mainStack);
	env->executedByteCount++;
	env->executedOpcodeCount++;
}

void OpDup(ScriptInterpreter *env)
{
	StackElement element = StackPop(&env->mainStack);
	StackPush(&env->mainStack, element);
	StackPush(&env->mainStack, element);
	env->executedByteCount++;
}

void OpDepth(ScriptInterpreter *env)
{
	/*  FIXME: Does not work if stack size is greater than 256 -- (more than one byte) */
	StackElement element;
	element.element[0] =  env->mainStack.stackSize;
	element.elementSize = 1;
	StackPush(&env->mainStack, element);
	env->executedByteCount++;
}


void ExecuteOpcodes(ScriptInterpreter *env)
{
	U8 opcode = env->script.bytes[env->executedByteCount];
	if ((0x00 <= opcode) && (opcode <= 0x60))
		ExecutePushDataOpcodes(env);
	else if (((OP_RETURN_187 <= opcode) && (opcode <= OP_RETURN_254)) || (opcode == OP_RETURN))
		env->scriptExecutionStatus = SCRIPT_FAILURE;
	else if ((OP_1ADD <= opcode) && (opcode <= OP_WITHIN))
		ExecuteMathopcodes(env);
	switch (opcode)
	{
		case OP_NOP				:	env->executedByteCount++; env->executedOpcodeCount++;	break;
		case OP_VER				:															break;
		case OP_IF				:															break;
		case OP_NOTIF			:															break;
		case OP_VERIF			:															break;
		case OP_VERNOTIF		:															break;
		case OP_ELSE			:															break;
		case OP_ENDIF			:															break;
		case OP_VERIFY			:	OpVerify(env);											break;
		case OP_EQUAL			:	OpEqual(env);											break;
		case OP_EQUALVERIFY		:	OpEqual(env); OpVerify(env); env->executedByteCount--;	break;
		case OP_RETURN			:	/* Implemented in OP_RETURN conditions */				break;

		/* --- STACK OPERATORS --- */
		case OP_TOALTSTACK		:	OpToAltStack(env);										break;
		case OP_FROMALTSTACK	:	OpFromAltStack(env);									break;
		case OP_2DROP			:															break;
		case OP_2DUP			:															break;
		case OP_3DUP			:															break;
		case OP_2OVER			:															break;
		case OP_2ROT			:															break;
		case OP_2SWAP			:															break;
		case OP_DROP			:	OpDrop(env);											break;
		case OP_DUP				:	OpDup(env);												break;
		case OP_NIP				:															break;
		case OP_OVER			:															break;
		case OP_ROLL			:															break;
		case OP_ROT				:															break;
		case OP_SWAP			:															break;
		case OP_TUCK			:															break;

		case OP_PICK			:															break;
		case OP_DEPTH			:	OpDepth(env);											break;
		default					:	printf("Error: Unsupported Opcode\n");
	}
env->executedOpcodeCount++;

}


