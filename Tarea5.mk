Results_hw5.pdf: Results_hw5.tex
	pdflatex Results_hw5.tex
Results_hw5.tex: modelo.png
modelo.png: Plots.py parametros.dat
	python Plots.py
parametros.dat: CurvaRotacion.c RadialVelocities.dat
	sed -i '1d' RadialVelocities.dat
	cc  CurvaRotacion.c -o kk.x -lm
	./kk.x > parametros.dat
	
	
	

