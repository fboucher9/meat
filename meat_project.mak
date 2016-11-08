# See LICENSE for license details

# meat - My Events And Television programs

ifndef MEAT_SRC_PATH
MEAT_SRC_PATH = .
endif

ifndef MEAT_DST_PATH
MEAT_DST_PATH = .
endif

ifndef MEAT_CC
MEAT_CC = $(CC)
endif

ifndef MEAT_CFLAGS
MEAT_CFLAGS := $(CFLAGS) -ansi -pedantic -Wall -Wextra -g -O0 -I$(MEAT_DST_PATH)
endif

ifndef MEAT_LDFLAGS
MEAT_LDFLAGS := $(LDFLAGS) -rdynamic
endif

MEAT_SRCS := \
    $(MEAT_DST_PATH)/_obj_meat_os.o \
    $(MEAT_DST_PATH)/_obj_meat_main.o \
    $(MEAT_DST_PATH)/_obj_meat_list.o \
    $(MEAT_DST_PATH)/_obj_meat_heap.o \
    $(MEAT_DST_PATH)/_obj_meat_time.o \
    $(MEAT_DST_PATH)/_obj_meat_dbg.o \
    $(MEAT_DST_PATH)/_obj_meat_opts.o \
    $(MEAT_DST_PATH)/_obj_meat_game.o \
    $(MEAT_DST_PATH)/_obj_meat_file.o \
    $(MEAT_DST_PATH)/_obj_meat_trace.o

.PHONY: all
all: $(MEAT_DST_PATH)/meat

$(MEAT_DST_PATH)/meat : $(MEAT_SRCS)
	@echo linking $@
	@echo -o $@ $(MEAT_CFLAGS) $(MEAT_SRCS) $(MEAT_LDFLAGS) > $(MEAT_DST_PATH)/_obj_meat.cmd
	@$(MEAT_CC) @$(MEAT_DST_PATH)/_obj_meat.cmd

# Build each object file
$(MEAT_DST_PATH)/_obj_%.o : $(MEAT_SRC_PATH)/%.c
	@echo compiling $@
	@echo -c -o $@ $(MEAT_CFLAGS) -MT $@ -MMD -MP -MF $@.d $< > $@.cmd
	@$(MEAT_CC) @$@.cmd

# Build the precompiled header
$(MEAT_DST_PATH)/meat_os.h.gch : $(MEAT_SRC_PATH)/meat_os.h
	@echo generating $@
	@$(MEAT_CC) -c -o $@ $(MEAT_CFLAGS) $(MEAT_SRC_PATH)/meat_os.h

.PHONY: clean
clean:
	@echo cleanup
	@rm -f $(MEAT_DST_PATH)/meat
	@rm -f $(MEAT_DST_PATH)/_obj_*
	@rm -f $(MEAT_DST_PATH)/*.gch

-include $(MEAT_DST_PATH)/_obj_*.o.d
