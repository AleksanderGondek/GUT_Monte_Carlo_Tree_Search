###### Gdansk University of Technology: Manycore Architectures Project

Parallel Monte Carlo Tree Search using Xeon Phi device
======

This project is an attempt to understand, implement, parallelize Monte Carlo Tree Search algorithm and investigate it's performance on _Intel Xeon Phi_ device. Whole exercise is done for Manycore Architectures classes at Gdansk University of Technology.

### Algorithm overview

We can describe Monte-Carlo Tree Search as a heuristic algorithm used to make most optimal decisions in given decision processes. It is most notably used to predict the best moves in general game playing. Aforementioned algorithm is becoming very popular and there are very good reasons for it.
First of all, we need to mention that for a very long period of time, another method (alfa-beta pruning) was prominent in the field of decision making algorithms for games – however this has changed in 2006 when MCTS was introduced in the field of playing Go. Since then MCTS is only getting more and more popular and dominant – that is because, compared to alfa-beta pruning, MCTS needs only implemented game mechanics to work, which is a huge advantage – MCTS can play games without developed theory, even (or mostly) general gaming. Moreover, game in MCTS is played in asymmetric manner, where algorithm is focusing only on the most promising parts. Lastly MCTS can be safely interrupted at any time of its execution and still return valid game move – it’s value depends on time spend on its prediction.
Due to mentions advantages over alfa-beta search, MCTS is getting widely adopted both in scientific projects as in computer games (i.e. many “bots” created to play online games rely on MCTS). 

### Chosen game to implement

As a simple game that is perfectly fit for MCTS to play I have chosen classic chess. Therefore this implementation of MCTS is dealing strictly with solving certain situations on chessboard. This may be changed with minimal efford - because class representing game states is implemented as "interface". You may inherit from it and implement any game. However the part of the code responsible for loading up starting state and displaying game are not ready for it and will have to be adjusted.

> Important note!
> 
> The code responsible for returning possible chess moves is not 100% ready.
> It will return onyl moves for king and pawns. Implementing rest is trivial but time-consuming and may be done in futre.

### Serial implementation overview

![alt tag](https://raw.github.com/AleksanderGondek/GUT_Monte_Carlo_Tree_Search/master/assets/SchemeOfMCTS.png)

Monte Carlo Tree Search is algorithm based on semi-randomized exploration on given search space. It uses the results of previous explorations to continuously build game tree, due to which it become increasingly better at given game, with each exploration performed. This also increased the accuracy of estimating which move is better.
Each run of the algorithm that is used to expand the game tree is called “playout”. In each playout the algorithm is playing the game to the end (or timeout) and then it uses the game playout outcome to weight the tree nodes so that in future better nodes (moves) ale more likely to be selected.

We can differentiate four different rounds of MCTS playout:

1. **Selection step** - the algorithm is selecting successive nodes, starting from the tree root. It basically takes the best known moves from the start of the game tree, to its leaf. How this selection is performed depends on chosen strategy – the main difficulty lies in balancing both three exploration and xploitation of previously added values.
The most popular and first formula for achieving such balance is called “Upper Confidence Bound  applied to tree” (UTC) and was used in my mplementation.
2. **Expansion step** - if the chosen tree leaf (move) ends the game, the playout jumps to backpropagation step. Otherwise it chooses one or more available moves and adds them as childes of the node.
3. **Simulation step** - the game is simulated and played to the end from each added new node.
4. **Backpropagation step** - After the simulation is done, the outcome of playout is propagated to each node from the last
one to the root.

As it was mention before, you can notice that the playout can be stopped at any time, however the
longer it plays the better it becomes in choosing the best possible moves. 


### Parallel implementation overview

![alt tag](https://raw.github.com/AleksanderGondek/GUT_Monte_Carlo_Tree_Search/master/assets/SchemeOfParallelMCTS.png)

In considering MCTS parallelization I will be focusing on symmetric multiprocessor (SMP) computers due to the fact that the application has to run on Xeon Phi device and I will be using OpenMP as my parallelization tool. Due to this I am using shared memory as a relatively low-latency way of
intercommunication. One could observe that in each MCTS playout, all except one rounds are touching and modifying the game tree. Only step 3 (simulation) is performing independent calculations and does not need to access or modify game tree during its performance. This is very important observations, because it highlights where data synchronization will be needed if given step is parallelized. It can be seen that running
parallelization only in playout step three may be efficient. Broadly speaking we can distinguish three ways of parallelizing MCTS algorithm: leaf parallelization, root parallelization and tree parallelization.

#### Using Leaf Parallelization

This way of performing MCTS parallelization may be perceived as most intuitive one. It was proposed by Cazenave and Jouandeau and it takes the advantage of previously mention fact that the playout step 3 (simulation) is independent. In short, the MCTS runs as a serial code, until
entering simulation step. There, instead choosing only one node to play to the end (or many in serial manner) we are running all possible nodes in parallel. Due to this approach we will be propagating all possible outcomes, instead of one. This seems easy and does not require any mutexes – however it is highly unpredictable, takes at average more time playing out only one game and may lead to wasting computational power.
This approach was the first implementation of my attempt to parallelize MCTS. 

#### Using Root Parallelization

This is another way of MCTS parallelization proposed by Cazenave. In simple terms it consists of building multiple game trees, one for each thread. They do not share information with each other. At the end, after all playouts are finished, all those game trees are merged and based on
the merged tree the best move is selected. This approach requires very scare communication and does not suffer from some of the Leaf Parallelization issues. I have implemented this way of parallelizing MCTS in my second, improved attempt.

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