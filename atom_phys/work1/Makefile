NAME=work1
DATE = $(shell date --rfc-3339="seconds" | cut -d "+" -f1 )

all:
	perl -e 's/%%%date%%%/$(DATE)/g' -pi ./$(NAME).tex
	pdflatex $(NAME).tex
	zathura $(NAME).pdf
	perl -e 's/$(DATE)/%%%date%%%/g' -pi ./$(NAME).tex 

clean:
	$(RM) *.aux *.log
