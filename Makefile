.DEFAULT_GOAL := help

ESY = esy
DUNE = esy dune
MEL = esy mel

.PHONY: install
install:
	$(ESY) install

.PHONY: client-bundle
client-bundle: ## Bundle the JS code
	node bundle.mjs

.PHONY: client-bundle-watch
client-bundle-watch: ## Watch and bundle the JS code
	node bundle.mjs --watch

.PHONY: client-build
client-build: ## Build Reason code
	$(DUNE) build @client

.PHONY: client-build-watch
client-build-watch: ## Watch reason code
	$(DUNE) build @client -w

.PHONY: server-build
server-build: ## Build the project, including non installable libraries and executables
	$(DUNE) build @@default

.PHONY: server-build-prod
server-build-prod: ## Build for production (--profile=prod)
	$(DUNE) build --profile=prod @@default

.PHONY: server-start
server-start: ## Start the server
	$(DUNE) exec --root . server/server.exe

.PHONY: server-dev
server-dev: ## Build in watch mode
	$(DUNE) build -w @@default

.PHONY: clean
clean: ## Clean artifacts
	$(DUNE) clean

.PHONY: format
format: ## Format the codebase with ocamlformat/refmt
	$(DUNE) build @fmt --auto-promote

.PHONY: format-check
format-check: ## Checks if format is correct
	$(DUNE) build @fmt

.PHONY: help
help: ## Print this help message
	@echo "";
	@echo "List of available make commands:";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";
