NAME = pvalues

all : $(NAME).ps $(NAME)

$(NAME) : $(NAME).cc

clean:
	$(RM) $(NAME) $(NAME).ps $(NAME).aux *.o *~ $(NAME).log $(NAME).dvi *.aux

%.ps : %.dvi
	@dvips -Ppdf -t letter $< -o

%.dvi : %.tex
	@latex $<
	@latex $<
