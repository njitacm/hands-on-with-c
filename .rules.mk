# .rules.mk -- the `make run` and `make check` rules shared by every challenge
#
# What attendees type:
#   make                    build every program
#   make run                run the challenge's program (lists the choices if there are several)
#   make run <NAME> [ARGS]  run program NAME, optionally with arguments
#   make check              test every program; prints __SUCCESS__ when all pass
#   make check all          same as `make check`
#   make check <NAME>...    test only the named program(s)
#
# Each challenge's Makefile says how to BUILD its programs, sets the
# variables below, and includes this file on its last line.
#
#   TESTED  = programs that `make check` tests; each has a tests/<name>/ folder
#   EXTRAS  = the challenge's other programs (demos, predict-the-output, bug hunts)
#
# Optional, for a program <name>:
#   RUN_ARGS_<name>  = arguments `make run <name>` uses when you don't give any
#   RUN_INPUT_<name> = file `make run <name>` feeds to stdin, unless you pipe
#                      input in yourself (echo "3 4" | make run <name>)
#   RUN_CMD_<name>   = how to start the program, if not ./<name>
#   CHECK_CMD_<name> = what the tests run, if not ./<name>
#
# Optional, for the whole challenge:
#   NOT_IN_ALL = programs plain `make` should skip (e.g. ones broken on purpose)

PROGRAMS := $(TESTED) $(EXTRAS)
CHECK    := ../../.check.sh

.DEFAULT_GOAL := all

_goals := $(MAKECMDGOALS)

# Quiet mode hides make's "'NAME' is up to date." chatter when NAME is used as
# a program name. Compiler warnings and errors still show.
ifneq ($(filter run check,$(_goals)),)
  MAKEFLAGS += -s
endif

# ---- make run [NAME [ARGS...]] ---------------------------------------------

# Words after `run` pick the program and its arguments.
ifeq ($(firstword $(_goals)),run)
  _run_words := $(wordlist 2,$(words $(_goals)),$(_goals))
endif
_run_prog := $(firstword $(_run_words))
_run_args := $(wordlist 2,$(words $(_run_words)),$(_run_words))

ifeq ($(_run_prog),)
  # No program named: use the challenge's only tested program, if there is one.
  ifeq ($(words $(TESTED)),1)
    _run_prog := $(TESTED)
  endif
else ifeq ($(filter $(_run_prog),$(PROGRAMS)),)
  $(error '$(_run_prog)' is not a program in this challenge. Choose from: $(PROGRAMS))
endif

# make treats the arguments as goals too. Let them quietly do nothing.
ifneq ($(_run_args),)
  .DEFAULT: ; @:
endif

_run_cmd   = $(strip $(or $(RUN_CMD_$(_run_prog)),./$(_run_prog)) $(or $(_run_args),$(RUN_ARGS_$(_run_prog))))
_run_input = $(RUN_INPUT_$(_run_prog))

run: $(_run_prog)
ifeq ($(_run_prog),)
	@echo "This challenge has more than one program. Run one with:"
	@for p in $(PROGRAMS); do echo "    make run $$p"; done
else ifneq ($(_run_input),)
	@if [ -t 0 ]; then $(_run_cmd) < $(_run_input); else $(_run_cmd); fi
else
	@$(_run_cmd)
endif

# ---- make check [all | NAME...] --------------------------------------------

ifneq ($(filter check,$(_goals)),)
  _check_names := $(filter-out check all clean,$(_goals))
  _unknown     := $(filter-out $(TESTED),$(_check_names))
  ifneq ($(_unknown),)
    $(error '$(firstword $(_unknown))' has no tests. Programs with tests: $(TESTED))
  endif
endif
_check_progs := $(or $(_check_names),$(TESTED))

# Leave out __SUCCESS__ unless every tested program is being checked.
_partial := $(if $(filter-out $(_check_progs),$(TESTED)),--partial)

check: $(_check_progs)
	@$(CHECK) $(_partial) $(foreach p,$(_check_progs),$(or $(CHECK_CMD_$(p)),./$(p)) tests/$(p))

# ---- make / make all -------------------------------------------------------

# In `make check all`, "all" just means "every program", so it builds nothing
# extra (only the tested programs, which check needs anyway).
ifneq ($(filter check,$(_goals)),)
all: ; @:
else
all: $(filter-out $(NOT_IN_ALL),$(PROGRAMS))
endif

.PHONY: all run check
