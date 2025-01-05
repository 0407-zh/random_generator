CXX      = clang++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I./include

OUTDIR   = build

TARGET   = random_generator

SRCS = src/Config.cpp \
       src/Storage.cpp \
       src/RandomGenerator.cpp \
       src/CommandHandler.cpp \
       main.cpp

OBJS = $(patsubst src/%.cpp, $(OUTDIR)/%.o, \
       $(filter src/%.cpp,$(SRCS))) \
       $(if $(filter main.cpp,$(SRCS)),$(OUTDIR)/main.o,)

all: $(OUTDIR)/$(TARGET)

$(OUTDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 规则：编译 src/xxx.cpp -> build/xxx.o
$(OUTDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTDIR)/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTDIR)

.PHONY: all clean