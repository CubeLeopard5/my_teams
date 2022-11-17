$@

RULES = client server tests

all: $(RULES)

$(RULES):
	make -C $@

re clean fclean all:
	make -C client $@
	make -C server $@
	make -C tests $@

.PHONY: $(RULES)