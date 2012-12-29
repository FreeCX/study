NAME=work2
DATE = $(shell date --rfc-3339="seconds" | cut -d "+" -f1 )

all:
	cat $(NAME).tex | sed "s/%%%date%%%/$(DATE)/g" | pdflatex
	zathura $(NAME).pdf

clean:
	$(RM) *.aux *.log
