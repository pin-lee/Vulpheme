## Data Sources
Vulpheme would not be possible without the work of the open source community. We all stand on each other's shoulders, forming a lattice of giants upon which to continue to build glorious feats. As such, it is vitally important to recognize and credit those who we have built upon.
### WordNet - Princeton University
The WordNet database gives Vulpheme life. Without it, Vulpheme is only a record-keeping markdown compiler. If you are able, please donate to https://wordnet.princeton.edu/, and contact those in charge of Princeton to fund their linguistics and computer science departments better.
### morphemes - Colin Goldberg
The morphemes dataset built by Colin Goldberg greatly increases the granularity that Vulpheme is able to operate at https://github.com/colingoldberg/morphemes. The morphemes set allows Vulpheme to determine positivity or negativity and better relate concepts.

---

**Both *morphemes* and *WordNet* have made possible the language processing faculties of Vulpheme. Without these intricately structured, labor-intensive works of data assembly, I would have to either take years of my life to assemble an inferior dataset by hand or steal the works of millions to build an inefficient, dirty deep learning model, which isn't even any fun. To the computational linguists of Princeton University and Colin Goldberg, I thank you very much.**

Additional credit is also due to the millions who have contributed to the C programming language, Linux, and all other open source software. Thank you, thank you very much. Thank you Meson developers, for making a substantially less bad build system.

---
# Vulpheme
Vulpheme is an organizational tool for publishing written content. It aims to provide concept mapping faculties via graph-based n-gram analysis, with concepts emerging as clusters of related linguistic data. Emphasis is placed on ease of reading published (compiled) content, with minimal visual clutter. Concept mapping and other methods to improve visual accessibility exist in order to serve those who struggle with perceiving and processing information, such as neurodivergent and otherwise perceptually impaired people.

As to technical design, strong emphasis is placed on designing and implementing the software with data-oriented design, acknowledging that the computer is a real machine and using the hardware to the best of our ability. For example, the graph database is implemented in SQL on top of SQLite, following the form normalization techniques discussed by Richard Fabian in his book *Data Oriented Design.* The computer doesn't know what a graph is, so it is the job of the designer (me) to architect software which is focused on the actual data transformations, not to force a world model onto an abstract ideal of a computing device.

Functionality and faculties are implemented largely from scratch, using standard libraries available on Linux. SQLite3 is chosen as a database system, as it is lightweight, performant, much better than I could do, and because I do (did) not have the time, energy, or expertise in database program design required to build one from scratch.
