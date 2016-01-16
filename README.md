###### Gdansk University of Technology: Manycore Architectures Project

Parallel Monte Carlo Tree Search using Xeon Phi device
======

This project is an attempt to understand, implement, parallelize Monte Carlo Tree Search algorithm and investigate it's performance on _Intel Xeon Phi_ device. Whole exercise is done for Manycore Architectures classes at Gdansk University of Technology.

### Algorithm overview

![alt tag](https://raw.github.com/AleksanderGondek/GUT_Monte_Carlo_Tree_Search/master/assets/SchemeOfMCTS.png)

### Serial implementation overview

T.B.D

### Parallel implementation overview

![alt tag](https://raw.github.com/AleksanderGondek/GUT_Monte_Carlo_Tree_Search/master/assets/SchemeOfParalellMCTS.png)

T.B.D

#### Using Leaf Parallelization

T.B.D.

#### Using Root Parallelization

T.B.D

### Sources in docs directory

This section describes the contents of docs directory. I have put there all important documents that had helped me in understanding and developing MCTS in parallel for Xeon Phi device. Hopefully this will help someone. 

* **DistributedMCTS** - Kazuki Yoshizoe, Akihiro Kishimoto, Tomoyuki Kaneko, Haruhiro Yoshimoto, Yutaka Ishikawa, "_Scalable Distributed Monte-Carlo Tree Search_" - very plesant to read paper, focusing on how to distribute MCTS algorithm, although it also happens to explain very clearly it's basic.
* **MultithreadedMCTS** - Guillaume M.J-B. Chaslot, Mark H.M. Winands, and H. Jaap van den Herik, "_Parallel Monte-Carlo Tree Search_" - paper that greatly explains MCTS basics and presents basic approaches to it's parallelization as well as it's implementation overheads. This was the base for choosing the approach to parallelization.
* **TutorialMCTS** - Michèle Sebag, "_Monte-Carlo Tree Search_" - short presentation detailing why MCTS algorithm is so popular and why it will become even more prominent. It also explains how does it work.
* **LinkToGoodTutorial** - Link to [this page](http://jeffbradberry.com/posts/2015/09/intro-to-monte-carlo-tree-search/) - basically the best explanation, step-by-step of MCTS algorith that I could find. 
* **OpenMP_Common_mistakes** - Michael Süß, Claudia Leopold, "_Common Mistakes in OpenMP and How To Avoid Them, A Collection of Best Practices_" - great paper describing common pitfalls of OMP programming.
* **GUTSlidesManycores** - Pawea Czarnul, "_Manycores Architectures_" - complete slides from the classes on subject of Manycores Architectures. Many interesting details about OMP and Xeon Phi devices.
* **BestPracticeGuide** - Michaela Barth, Mikko Byckling, Nevena Ilieva, Sami Saarinen, Michael Schliephake, and Volker Weinberg, "_Best practice guide - Intel Xeon Phi_" - Great document in details describing how to develop applications directly for Xeon Phi devices, and how to utilize OMP potential. Available [here](http://www.prace-ri.eu/IMG/pdf/Best-Practice-Guide-Intel-Xeon-Phi.pdf).

### Appropriates

* The images previewing how Monte-Carlo Tree Search Algorithm work, and how it's parallelizations work, were borrowed from the following paper: Parallel Monte-Carlo Tree Search by Guillaume M.J-B. Chaslot, Mark H.M. Winands, and H. Jaap van den Herik.