/*
 * Challenge 2: Pointer Arithmetic & Arrays
 *
 * Fill in the four functions below (Exercises 1-4), then:
 *
 * Try it:
 *     echo "strlen hello" | make run ptrs
 *
 * Test it:
 *     make check ptrs
 *
 * The rule for this file: walk memory with POINTERS (p++, *p, p < end),
 * not with array indexes like s[i]. Don't call the real strlen/strcpy.
 * 
 * The (void) lines only silence "unused parameter" warnings; delete them.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

/* Exercise 1: count the characters before the '\0'. */
size_t my_strlen(const char *s)
{
    /* TODO (Exercise 1): move a pointer `p` from `s` to the '\0',
     * then return p - s. */
    (void)s;
    return 0;
}

/* Exercise 2: copy `src` (including its '\0') into `dst` and return `dst`. */
char *my_strcpy(char *dst, const char *src)
{
    /* TODO (Exercise 2): copy one char at a time until you've copied the '\0'.
     *
     * Remember to return the ORIGINAL `dst`. */
    (void)src;
    dst[0] = '\0';
    return dst;
}

/* Exercise 3: reverse arr[0..n-1] in place using two pointers. */
void reverse(int *arr, size_t n)
{
    /* TODO (Exercise 3): `lo` starts at the first element, `hi` at the last.
     * Swap `*lo` and `*hi` and move them toward each other until they meet.
     *
     * What happens if `n` is 0? */
    (void)arr;
    (void)n;
}

/* Exercise 4: return a pointer to the first element equal to target,
 * or NULL if there isn't one. */
int *find(int *arr, size_t n, int target)
{
    /* TODO (Exercise 4): loop with `for (int *p = arr; p < arr + n; p++)` */
    (void)arr;
    (void)n;
    (void)target;
    return NULL;
}

/* ------------------------------------------------------------------------
 * Test driver. You don't need to change anything below this line.
 *
 * It reads commands from stdin, one per line:
 *     strlen TEXT              (TEXT is the rest of the line, it may be empty)
 *     strcpy TEXT
 *     reverse V1 V2 ... VN
 *     find TARGET in V1 V2 ... VN
 * ------------------------------------------------------------------------ */
#define MAX_LINE   256
#define MAX_VALUES 100

/* Read whitespace-separated ints from `text` into `vals`, return how many. */
static size_t parse_ints(const char *text, int vals[], size_t max)
{
    size_t n = 0;
    int used;
    while (n < max && sscanf(text, "%d%n", &vals[n], &used) == 1) {
        text += used;
        n++;
    }
    return n;
}

/* If line starts with the word `cmd`, return what follows it, else NULL. */
static const char *arg_after(const char *line, const char *cmd)
{
    size_t len = strlen(cmd);
    if (strncmp(line, cmd, len) != 0)
        return NULL;
    if (line[len] == ' ')
        return line + len + 1;
    if (line[len] == '\0')
        return line + len;
    return NULL;
}

int main(void)
{
    char line[MAX_LINE];
    const char *arg;

    while (fgets(line, sizeof line, stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';           /* drop the newline */

        if ((arg = arg_after(line, "strlen")) != NULL) {
            printf("strlen(\"%s\") = %zu\n", arg, my_strlen(arg));
        } else if ((arg = arg_after(line, "strcpy")) != NULL) {
            char buf[MAX_LINE];
            memset(buf, 'X', sizeof buf);           /* make a missing '\0' visible */
            buf[sizeof buf - 1] = '\0';
            char *ret = my_strcpy(buf, arg);
            printf("strcpy: \"%s\" (%s dst)\n", buf,
                   ret == buf ? "returned" : "did NOT return");
        } else if ((arg = arg_after(line, "reverse")) != NULL) {
            int vals[MAX_VALUES];
            size_t n = parse_ints(arg, vals, MAX_VALUES);
            reverse(vals, n);
            printf("reverse:");
            for (size_t i = 0; i < n; i++)
                printf(" %d", vals[i]);
            printf("\n");
        } else if ((arg = arg_after(line, "find")) != NULL) {
            int target, used = -1, vals[MAX_VALUES];
            if (sscanf(arg, "%d in%n", &target, &used) != 1 || used < 0)
                continue;
            size_t n = parse_ints(arg + used, vals, MAX_VALUES);
            int *hit = find(vals, n, target);
            if (hit == NULL)
                printf("find: %d not found\n", target);
            else
                printf("find: %d found at index %td\n", target, hit - vals);
        } else if (line[0] != '\0') {
            printf("unknown command: %s\n", line);
            return 1;
        }
    }
    return 0;
}
