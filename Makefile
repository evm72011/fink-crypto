BUILD_DIR  := build/wsl
BUILD_TYPE := Debug # Release

WSL_CONFIGURE_PRESET := wsl-ninja-$(shell echo $(BUILD_TYPE) | tr A-Z a-z)

RED   := \033[31m
GREEN := \033[32m
GRAY  := \033[90m
RESET := \033[0m

.PHONY: all venv conan_install configure build run test clang_tidy clang_format cmake_format docs clean

all: clean conan_install configure build run

venv:
	@bash scripts/wsl/bootstrap-venv.sh

conan_install: clean
	@$(CONAN) --version
	@$(CONAN) install . \
	-s build_type=$(BUILD_TYPE) \
	-s compiler.cppstd=23 \
	--output-folder=$(BUILD_DIR) --build=missing

configure:
	cmake --preset $(WSL_CONFIGURE_PRESET)

build:
	@cmake --build $(BUILD_DIR); rc=$$?; \
	if [ $$rc -ne 0 ]; then \
		printf "$(RED)Build FAILED$(RESET)\n"; exit $$rc; \
	fi; \
	printf "$(GREEN)Build OK$(RESET)\n"

run: build fink-crypto-cli