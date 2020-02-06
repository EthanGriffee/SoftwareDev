This report is meant to outline the pros and cons of the 6 selected assignments, using
various tests to back up various assertions and conclude which of the assignments would
be the best data adaptor to use moving forward.

Originally team OHE was going to be used, but one of our tests produced a Segfault.

Description of the analysis performed - describe your benchmarks, why and how you created them. Describe what you are going to measure and how. (e.g. builds vs. runs vs. iterations) Describe also the HW/SW infrastructure (OS, docker?, compiler, ...)

Comparison of the products’ relative performance Include graphs and an ordered list (best first). Avoid single runs. Describe the sources of non-determinism.

Threats to validity What could make your results wrong for someone else?

Recommendation to management which consists of a list of the projects in order of preference, and a rationale for your top choice (consider also code quality and effort to integrate).


One test we ran included the string <"dsfsaD><Dsafsa">. The behavior of this was not 
explicitly defined in the Project guidlines, but we were interested to see how each
project hadnled it. 

TeamBaobab, Prizes - Parses into two Strings:  dsfsa, Dsafsa"
            This does not make much sense because it removes the beginning " and the D
            at the end of the first string, when it should be checking if the D is a "

Anonymous - Parses into two empty strings: 
            This means that the code probably sees it as two strings "dsfsaD and Dsafsa."
            But, they decide it's "malformed," and makes it an empty string. This behavior
            does not make sense as they are throwing out data, and was not specified in the
            Assignment.  

Chunky Boys - Parses into two strings: "dsfsaD, "Dsafsa""
            This does not make much sense as the first string is not given quotes, while the
            second string is. 

Snowy Song - Parses into two strings: ""dsfsaD", "Dsafsa""
            This makes sense as it prints them like strings, adding quotations around it.

Purgatory - Parses into two strings: "dsfsaD, Dsafsa"
            This makes sense as they are not changed.