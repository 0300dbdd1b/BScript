#include "include/ScriptInterpreter.h"
#include "include/opcodes.h"

/* -------------------------- STACK --------------------------------- */
void StackPush(Stack *stack, StackElement element)
{
    if (stack->stackSize >= MAX_STACK_SIZE)
	{
        printf("Error: Stack overflow\n");
        return;
    }
    stack->elements[stack->stackSize] = element;
	stack->stackSize++;
}

StackElement StackPop(Stack *stack)
{
    if (stack->stackSize == 0)
	{
        printf("Error: Stack underflow\n");
        StackElement empty = {0};
        return empty;
    }
	stack->stackSize--;
    return stack->elements[stack->stackSize];
}

void PrintStacks(Stack *mainStack, Stack *altStack) {
	printf("Size | Main Stack            | Size | Alt Stack\n");
	printf("-----|-----------------------|------|----------------------\n");
	size_t maxSize = mainStack->stackSize > altStack->stackSize ? mainStack->stackSize : altStack->stackSize;

	for (size_t i = 0; i < maxSize; i++)
	{ if (i < mainStack->stackSize) {
			printf("%-4zu | ", mainStack->elements[i].elementSize);
			for (size_t j = 0; j < mainStack->elements[i].elementSize; j++)
				printf("%02X", mainStack->elements[i].element[j]);
			for (size_t j = mainStack->elements[i].elementSize * 2; j <= 21; j++) // NOTE: Pad remaining space
				printf(" ");
		}
		else
			printf("     |                    ");

		printf("| %-4zu | ", i < altStack->stackSize ? altStack->elements[i].elementSize : 0);
		if (i < altStack->stackSize)
		{
			for (size_t j = 0; j < altStack->elements[i].elementSize; j++)
				printf("%02X", altStack->elements[i].element[j]);
			for (size_t j = altStack->elements[i].elementSize * 2; j < 20; j++)
				printf(" ");
		}
		printf("\n");
	}
}

/* -------------------------- SCRIPT --------------------------------- */
void InitScript(Script *script, const char *rawScript)
{
	if (IsHex(rawScript))
	{
		strcpy(script->hex, rawScript);
		hexStringToBytes(rawScript, script->bytes, MAX_SCRIPT_SIZE, &script->scriptSize);
	}
}

void PrintScript(Script *script)
{
    printf("script: %s\n", script->hex);
    printf("scriptSize: %zu\n", script->scriptSize);

    printf("Bytes: ");
    for (size_t i = 0; i < script->scriptSize; i++)
	{
        printf("%02X", script->bytes[i]);
        if (i < script->scriptSize - 1)
            printf(" ");
    }
    printf("\n");
}

void ScriptToHRF(Script *script)
{
}

void HRFToBytes(Script *script)
{
}


/* -------------------------- STANDARDNESS --------------------------------- */
U8 IsOpcodeStandard(OPCODE opcode)
{
	const OPCODE nonStandardOpcodes[] = {
		
	};
	return nonStandardOpcodes[opcode];
}
