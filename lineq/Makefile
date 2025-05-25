TARGET_DIR = target

srcs = $(wildcard src/*.cxx)
hdrs = $(wildcard include/*.hxx)
srcsoext = ${srcs:.cxx=.cxx.o}
dbgobjs = $(patsubst src/%,target/dbg/obj/%,${srcsoext})
relobjs = $(patsubst src/%,target/rel/obj/%,${srcsoext})

compileflags = $(shell tr "\n" " " < compile_flags.txt)
linkflags    = $(shell tr "\n" " " < link_flags.txt   )
CXXFLAGS += ${compileflags}
LDFLAGS  += ${linkflags}

OPTCXXFLAGS = -O3 -flto=thin
OPTLDFLAGS = -flto=thin

.PHONY: dbg rel
dbg: ${TARGET_DIR}/dbg/lineq
rel: ${TARGET_DIR}/rel/lineq

${TARGET_DIR}/dbg/lineq: ${dbgobjs} src
	@printf '  linking %s\n' $@
	@${CXX} -fdiagnostics-color=always ${CXXFLAGS} ${LDFLAGS} ${dbgobjs} -o $@
${TARGET_DIR}/rel/lineq: ${relobjs} src
	@printf '  linking %s\n' $@
	@${CXX} -fdiagnostics-color=always ${LDFLAGS} ${OPTLDFLAGS} ${relobjs} -o $@

${TARGET_DIR}/dbg/obj/%.cxx.o: src/%.cxx include ${hdrs} | ${TARGET_DIR}/dbg/obj
	@printf '  building %s\n' $<
	@${CXX} -fdiagnostics-color=always ${CXXFLAGS} -c $< -o $@
${TARGET_DIR}/rel/obj/%.cxx.o: src/%.cxx include ${hdrs} | ${TARGET_DIR}/rel/obj
	@printf '  building %s\n' $<
	@${CXX} -fdiagnostics-color=always ${CXXFLAGS} ${OPTCXXFLAGS} -c $< -o $@

${TARGET_DIR}/dbg/obj:
	@mkdir -p $@
${TARGET_DIR}/rel/obj:
	@mkdir -p $@

.PHONY: rundbg runrel clean tidy fmt
rundbg: target/dbg/lineq
	@$<
runrel: target/rel/lineq
	@$<
clean:
	rm -rf target
tidy:
	@clang-tidy --use-color ${srcs} -- ${CXXFLAGS}
