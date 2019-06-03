(TeX-add-style-hook
 "min-cost-flow"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "12pt" "a4")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("babel" "english")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art12"
    "inputenc"
    "graphicx"
    "caption"
    "float"
    "listings"
    "babel"
    "biblatex")
   (LaTeX-add-labels
    "sec:intro"
    "sec:modelling"
    "fig:modeled-graph"
    "subsec:vertex-structure"
    "subsec:arches"
    "sec:state-of-the-art"
    "subsec:min-mean-cycle-cancelling"
    "subsec:network-simplex"
    "fig:netwok-simplex-algorithm"
    "sec:important-mentions"
    "sec:solution"
    "subsec:dijkstra"
    "subsec:edmonds-karp"
    "sec:conclusion")
   (LaTeX-add-bibliographies
    "sample"))
 :latex)

