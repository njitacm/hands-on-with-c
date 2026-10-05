# Agenda

Every section presentation follows the same rhythm (borrowed from [Hands-On with Frontier](https://github.com/olcf/hands-on-with-frontier)):

1. **Short talk (10 to 20 min):** the presenter walks through the concept sections of a challenge README and live-codes the examples.
2. **Hands-on time (20 to 40 min):** attendees do the Exercises while helpers circulate. Success = `__SUCCESS__` from `make check`.
3. **Debrief (5 min):** go over one or two common mistakes you saw, then move on.

---

## Format A: One-Day Crash Course (about 6 hours)

This session covers just the essentials and leaves the rest of the workshop to the attendees as a self-paced exersize.

| Time | Topic | Challenges | Format |
|------|-------|------------|--------|
| 10:00 am | Welcome, why C, and setup | [Getting Set Up](./00-getting-set-up/) | Talk + hands-on |
| 10:20 am | Compiling, types, and printf | [1.1](./01-c-fundamentals/01-hello-world/), [1.2](./01-c-fundamentals/02-variables-and-types/) | Talk + hands-on |
| 11:00 am | Control flow and functions | [1.3](./01-c-fundamentals/03-control-flow/), [1.4](./01-c-fundamentals/04-functions/) | Talk + hands-on |
| 11:45 am | Arrays and strings | [1.5](./01-c-fundamentals/05-arrays-and-strings/) | Talk + hands-on |
| 12:15 pm | Lunch | | |
| 1:00 pm | Pointers, the big one | [2.1](./02-pointers-and-memory/01-pointers/), [2.2](./02-pointers-and-memory/02-pointer-arithmetic/) | Talk + hands-on |
| 1:50 pm | The heap and `argv` | [2.3](./02-pointers-and-memory/03-dynamic-memory/), [2.5](./02-pointers-and-memory/05-command-line-arguments/) | Talk + hands-on |
| 2:30 pm | Break | | |
| 2:40 pm | Finding bugs like a pro | [5.2](./05-tools-and-the-machine/02-debugging-with-gdb/), [5.3](./05-tools-and-the-machine/03-finding-memory-bugs/) | Live demo + hands-on |
| 3:20 pm | Bits and bytes | [3.1](./03-data-representation/01-number-systems/), [3.2](./03-data-representation/02-bitwise-operations/) | Talk + hands-on |
| 3:50 pm | Open challenge time | Anything, including the [Capstone](./06-going-further/05-capstone-pathfinder/) | Hands-on |
| 4:20 pm | Wrap-up and where to go next | | Talk |

---

## Format B: Weekly Evening Series (6 sessions, 90 minutes each)

Each session covers one section of the workshop, attendees finish the remaining challenges at home before the next session.

| Session | Section | In-session focus | Homework (self-paced) |
|---------|---------|------------------|-----------------------|
| 1 | Setup + [Section 1: C Fundamentals](./01-c-fundamentals/) | 1.1 to 1.3 | 1.4, 1.5 |
| 2 | [Section 2: Pointers & Memory](./02-pointers-and-memory/) | 2.1 to 2.3 | 2.4, 2.5 |
| 3 | [Section 3: Bits, Bytes & Data Representation](./03-data-representation/) | 3.1 to 3.3 | 3.4, 3.5 |
| 4 | [Section 4: Structs, Data Structures & Files](./04-structs-and-data-structures/) | 4.1, 4.2, 4.4 | 4.3, 4.5 |
| 5 | [Section 5: Tools & Under the Hood](./05-tools-and-the-machine/) | 5.1 to 5.3 | 5.4 to 5.6 |
| 6 | [Section 6: Going Further](./06-going-further/) | 6.1, then attendee's choice | Capstone (6.5) |

Suggested 90-minute session plan:

| Minutes | Activity |
|---------|----------|
| 0 to 10 | Recap last week; answer homework questions |
| 10 to 30 | Talk + live coding for the first challenge |
| 30 to 50 | Hands-on: first challenge |
| 50 to 65 | Talk + live coding for the second challenge |
| 65 to 85 | Hands-on: second challenge (third if time allows) |
| 85 to 90 | Preview next week; assign homework challenges |

**Scheduling tip:** CS288 reaches pointers around week 7, and CS350 reaches assembly around week 4 or 5. Schedule Sessions 2 to 5 a little *before* those weeks so the workshop functions as a preview, not a review.

---

## Format C: Two-Hour Intro (general body meeting or club fair)

Best for introducing new members to C with no assumption of prior knowledge / setup.

| Time | Topic | Challenges |
|------|-------|------------|
| 0:00 | Why C? Getting connected to AFS | [Getting Set Up](./00-getting-set-up/) (AFS option) |
| 0:15 | Your first program | [1.1 Hello, World!](./01-c-fundamentals/01-hello-world/) |
| 0:40 | Types and printf | [1.2 Variables, Types & printf](./01-c-fundamentals/02-variables-and-types/) |
| 1:10 | A taste of pointers | [2.1 Pointers & Addresses](./02-pointers-and-memory/01-pointers/) (first half) |
| 1:45 | How to keep going on your own; Q&A | This README |

---

## Self-Paced Path

Working alone? Follow the challenges in order and budget about **15 to 20 hours** in total:

| Section | Approx. time |
|---------|--------------|
| Getting Set Up | 15 min |
| 1: C Fundamentals | 2 to 3 hours |
| 2: Pointers & Memory | 3 to 4 hours |
| 3: Bits, Bytes & Data Representation | 2 to 3 hours |
| 4: Structs, Data Structures & Files | 3 hours |
| 5: Tools & Under the Hood | 3 to 4 hours |
| 6: Going Further | 2 to 4 hours, plus the capstone |
