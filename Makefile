$@

RULES = client server

all: $(RULES)

$(RULES):
	make -C $@

re clean fclean all:
	make -C client $@
	make -C server $@

.PHONY: $(RULES)