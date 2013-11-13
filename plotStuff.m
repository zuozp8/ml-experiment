clf

i=1;


function foo(out, i, titleSufix)
	epochs = 5;
	dataPerEpoch = 50;
	boolScore = out(1:2:end,:); learningScore = out(2:2:end,:);

	subplot(2,3,i)
	plot(learningScore)
	axis([0, (epochs*dataPerEpoch), 40500,  42000])
	set (gca, 'xtick', [0:epochs] * dataPerEpoch)
	set (gca, 'xticklabel', {'0', '1', '2', '3', '4', '5'})
	xlabel("Epoch")
	set (gca, "ygrid", "on")
	set (gca, "yminorgrid", "on")
	set (gca, "xgrid", "on")
	title(strcat("Learning Error", titleSufix))
	legend({"raw","10 000","100 000","500 000","average"})

	subplot(2,3,3+i)
	plot(boolScore)
	axis([0, epochs*dataPerEpoch, 0.227, 0.237])
	set (gca, 'xtick', [0:epochs] * dataPerEpoch)
	set (gca, 'xticklabel', {'0', '1', '2', '3', '4', '5'})
	xlabel("Epoch")
	set (gca, "ygrid", "on")
	set (gca, "yminorgrid", "on")
	set (gca, "xgrid", "on")
	title(strcat("Bool Error ", titleSufix))
	legend({"raw","10 000","100 000","500 000","average"})

endfunction

randSeed = time;
if (exist("newData", "var") && newData)
	system(sprintf("./experiment1	1	8	5	.2	%d> out1", randSeed));
	system(sprintf("./experiment1	1	8	5	1	%d> out2", randSeed));
	system(sprintf("./experiment1	1	8	5	5	%d> out3", randSeed));
endif

foo(load("out1"), 1, " (low learning speed)")
foo(load("out2"), 2, "")
foo(load("out3"), 3, " (high learning speed)")

pause(1)
print(sprintf("plot-%d.svg", randSeed))
pause(2)
print(sprintf("plot-%d.svg", randSeed))
