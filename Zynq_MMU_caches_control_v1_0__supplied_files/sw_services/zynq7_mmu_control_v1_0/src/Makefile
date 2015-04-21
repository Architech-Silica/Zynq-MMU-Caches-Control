COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=

RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I${INCLUDEDIR} 
ZYNQ7_MMU_CONTROL_DIR = .
               
LIB_SRCS = $(ZYNQ7_MMU_CONTROL_DIR)/mmu_control.c

ZYNQ7_MMU_CONTROL_SRCS = $(LIB_SRCS)

ZYNQ7_MMU_CONTROL_OBJS = $(ZYNQ7_MMU_CONTROL_SRCS:%.c=%.o)


EXPORT_INCLUDE_FILES = $(ZYNQ7_MMU_CONTROL_DIR)/include/mmu_control.h

libs: libzynq7_mmu_control.a
	cp libzynq7_mmu_control.a $(RELEASEDIR)
	make clean

include:
	@for i in $(EXPORT_INCLUDE_FILES); do \
	echo ${CP} -r $$i ${INCLUDEDIR}; \
	${CP} -r $$i ${INCLUDEDIR}; \
	done

clean:
	rm -rf obj/*.o
	rmdir obj
	rm libzynq7_mmu_control.a

libzynq7_mmu_control.a: obj_dir print_msg_isf_base $(ZYNQ7_MMU_CONTROL_OBJS)
	@echo "Creating archive $@"
	$(ARCHIVER) rc $@ obj/*.o

obj_dir:
	mkdir obj

print_msg_isf_base:
	@echo "Compiling Zynq7_MMU_Control Library"

.c.o:
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) -c $< -o obj/$(@F)
