# DP Framing

## Quick Tips

- To slow?
    - Reframe the problem
        - Can some dimensions be combined?
        - Can some dimensions be removed?
            - Maybe store part of the state as backtracking data
                - Make sure the backtracking storage is fully represented by the problem frame!
        - Can some dimensions be outsourced?
            - AKA: Can the deliverable be simplified and then modified later? (recombinind algebraic terms)
    - Make less decisions
        - Can you "collapse" the decisions to one end?
            - In range decisions, does order of ranges matter?
- Doesn't work?
    - Add dimensions
        - What would make the decision easier?
    - Add stages
        - Can you run a seperate dp which populates a table to help the larger one?

## Complexity and Limits
If running out of time (TLE):

- Frame the problem better? (less dimensions, smaller dimensions, outsource things)

If running out of space (MLE):

- Rolling array
    - How many iterations back do you need to look at? One? Two?
    - Swap vectors or arrays around with `std::swap`--It's O(1)
- State compression, pruning

## Frame the problem
- Sometimes states can be combined, such as a range colpasing to one end if order of "splitting" doesn't matter

## Subproblem Structures
**Common ways to frame the problem, organized by topological structure**

- Linear
    - Each subproblem only uses the solution of one smaller subproblem, although multiple may be considered.
    - 1d
        - `dp[i]` usually represents best value up to point `i`
        - `dp[i]` sometimes represents best value "using" point `i`, because more is not always "better" or "eaiser" in some problems
        - A problem using `dp[i][j]` may be considered one dimensional if `dp[i][j+1]` is completely unrelated to `dp[i][j]`, such as when `(i, j)` represents a node in a graph
            - These problems can be thought of as one dimensional `dp[(i, j)]`
        - If the topological structure of the problem (not of the equation) is a tree, then the problem is usually split by subtree.
            - Tree "dp" problems may not have overlapping subproblems, but are considered dp because they have similar solutions - you similarly need to think about subproblem structure and states.
            - Tree dp "sub dp"s usually use the height, weight, diameter, of subtrees.
    - 2d
        - `dp[i][j]` often represents a range in a 1d problem structure.
            - This often occurs when the value of `dp[0][i]` is not easily determinable from `dp[0][0:i]`
            - This also shows up when the problem itself involves segments and arbitrary splitting.
        - `dp[i][j]` can also represent the combinations between two 1d structures
            - For example, in the Longest Common Subsequence problem, where finding the subsequences are treated as two connected but independant problems.
        - `dp[i][j]` can represent two completely unrelated dimensions or constraints
            - eg. Knapsack problem, where both dimensions represent unrelated constraints that are modified using external mappings (arrays for value and weight of each item)
    - Higher Dimensions
        - Number of dimensions needed is usually the number of "independant" choices to optimize over.
- Tree
    - Similar to the linear structure of selecting "cut" locations, except the order of those cuts matters.
        - Where to "cut" is to choose from a range of options (such as indicies) along one dimension to split the problem into subproblems.
        - Where the order of selection matters (selecting indicies 1, 2, 3 is different from selecting 2, 1, 3).
        - Where the solution to a problem uses multiple subproblems, such as one for the left side and one for the right.
    - Because trees often deal with "segments" of the subproblem, they usually involve ranges (`dp[i][j]`)
        - The DP equation needs to select a way to "split" the subproblem, often by chosing `k : i < k < j`
        - The problem may incorporate multiple dimensions of splitting such as by chosing `a: i < a < j || b: k < b < l`, such as in DP23
- Graph
    - DP Equation represents value at each node, and includes a clause for every edge going out of the node, if some condition holds for that edge.
    - Problems with one "obvious" node may be longest path problems, which can be solved in `V+E` with a modified topological sort.
    - Problems with two "obvious" nodes may be shortest path or a variant.
    - Problems that care about all nodes are probably MST.
- Grid Graph
	- A graph DP problem on a multi-dimensional array/grid
	- No loop property is usually satisfied in two ways:
		- Coordinate based
			- For example: can only move to the right, can only move right and down/up
			- DP7
			- Can usually just simulate, taking the maximum of all options
		- External Factor
			- For example: external property `x` must increase/decrease with each step
			- DP21
			- Can usually sort by external factor and then do 1-d DP, or check all neighbors with an if condition
	- Use another array for path reconstruction, storing where you came from at each node
- Sub DP
    - If the dp equation for something is complete except requires knowing some property of the state, then it may be possible to run a "helper" dp to produce that value

## Per Problem
- PS : Problem Structure
    - What is the topological structure of the original problem?
    - What topological structures immedietly come to mind directly from the problem description?
- DC : Decision Complexity
    - How many subproblems are considered in the DP equation?
    - What is the branching factor of the recursive tree?
- SS : Subproblem Structure
    - How many subproblems are incorporated into each problem?
    - How many subproblems does the DP equation select and use?
        - 1: min/max, removing a constant chunk from the problem
        - 2: cutting the problem up
        - n: constant factor selection built into the problem
- SD : State Dimensionality
    - How complex is the state representation?
    - What attributes are needed to frame the problem?
    - How are optimal solutions to subproblems stored?
> **TODO: Linear subproblem structure currently means that the dp equation uses one subproblem in the final expression. A dp equation that uses two subproblems is considered `2b tree`. However, shouldn't both of these be considered constant, where the first has a subproblem dimensionality of `1` and the second of `2`? Linear subproblem structure *should* mean that the dp equation uses a linear complexity of subproblems.**

| Problem | PS | DC | SS | SD | Frame | Equation |
|---------|----|----|----|----|-------|----------|
Number Triangle | Tree-like | Constant | Linear | 2 | `dp[r][c]` = Best score going down from `(r, c)` | `dp[r][c] = min(dp[r+1][c], dp[r+1][c+1])`
0/1 Knapsack | 2d Linear | Constant | Linear | 2 | `dp[i][j]` = Most value obtainable from first `i` items and having atleast `j` capacity remaining in the knapsack | `dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i])`
DP1 (UVa 10003) Cutting Sticks | 1d Linear | Linear | 2b Tree | 2 | `dp[l][r]` = Minimum cost to cut the segment from cut `l` to `r` | `dp[l][r] = pos[r]-pos[l] + min({dp[l][k] + dp[k][r] : l < k < r})`
DP9 (UVa 11584) Subproblem | 1d Linear (range) | Constant | Linear | 2 | `dp[l][r]` = Whether the range from `l` to `r` is a palendrome | `dp[l][r] = dp[l-1][r-1] && str[l] == str[r]`
DP9 (UVa 11584) "partitioning into palendromes" | 1d Linear | Linear | < | 1 | `dp[i]` = Mininmum number of partitions to palendromify from `str[0]` to `str[i]` | `dp[i] = min({dp[j]+1 : 0 <= j < i if is_palendrome[j][i]})`
DP21 (UVa 10285) "longest run on a snowboard" | Grid Graph, 1d Linear | Constant | Linear | 1 | `dp[(r, c)]` = Longest decreasing sequence starting from `(r, c)` | `dp[r][c] = max({dp[(r', c')] : (r', c') is a neighbor of (r, c) if height[(r', c')] < height[(r, c)]})`
DP22* (UVa 10118) "Free Candies" | 4x Linear | Constant | 1d Linear | 4 | `dp[i, j, k, l]` = Most candies obtainable using the bottom `i` candies from the first pile, `j` from the second, etc. | `dp[i, j, k, l] = max(dp[i+1, j, k, l] + whether candy of color pile1[i] was already in the basket, same for j, etc)`

DP23 (UVa 1629) "Cake Slicing" | 2x 2b Tree | Linear | 2x 2b Tree | 4 | `dp[i, j, k, l]` = Minimum cost to cut cake bounded by `i <= x < k` and `j <= y < l` | `dp[i, j, k, l] = min({topCost + bottomCost + width : j < y < l if both sides have atleast one cherry} U {leftCost + rightCost + height : i < x < k if both sides have atleast one cherry})`
DP24 (UVa 1630) "Folding" | 1d Linear | Linear | 2b Tree | 1 | `dp[string]` = Minimum cost to fold `string` | `dp[string] = min({dp[string[:k]] + dp[string[k:]] : 0 < k < k.length-1}) if string is unfoldable **or** "${fold_count}(${dp[string[:prefix]]})"`
DP25 (UVa 242) "Stamps and Envelope Size" | 1d Linear | Linear | < | 1 | `dp[i]` = Minimum number of stamps to be worth `i` money | `dp[i] = min(dp[j] + 1 : 0 <= j < i if i-j is a valid denomination of stamp)`
Tree Max Points Without Direct Connection | Unbounded Tree | Constant | Unbounded Tree | 1 | `dp[i][0]` = best score in subtree of `i` without picking `i` and `dp[i][1]` = best score with picking `i` | `dp[i][0] = max{dp[k][0], dp[k][1] : k is a child of i}` and `dp[i][1] = max{dp[k][0] : k is a child of i} + 1` (+1 because we are picking `i`)
Tree Diameter* | Unbounded Tree | Linear | < | 1 | First, `height[i]` = the height of the subtree rooted at `i`. Then, `longest[i]` = longest path contained in the subtree rooted at `i` | `height[i] = max{height[k] : k is child of i}` and `longest[i] = max({longest[k] : k is child of i} U {height[l] + height[r] : l,r are children of i && l != r})` (longest[i] = longest of a subtree or sum of height of two subtrees)
Tree Minimum Centroid | Unbounded Tree | Linear | Linear | 1 | `weight[i]` = weight of the subtree rooted at `i`, and `cost[i]` = maximum weight of trees in the forest created by removing `i` | `weight[i] = sum{weight[k] : k is child of i} +1` and `cost[i] = max({weight[k] : k is child of i}, weight[root] - weight[i])` (`weight[root]-weight[i]` is the weight of the tree above the subtree `i`)
DP13 (UVa 12186) "Another Crisis" percentage to raise | Tree | Linear | x-branch tree | 1 | `dp[i]` = min leaf nodes needed to convince `i` | `dp[i] = (min T%){dp[k] : k ∈ i}`
DP14 (UVa 1220) "Party at Hali-Bula" tree max unconnected nodes | See "Tree Max Points Without Direct Connection" | < | < | < | < | < |
DP37 (tm 1039) "Annivesary Party" weighted max unconnected nodes | " | < | < | < | < | `dp[i][0]` = same as above; `dp[i][1] = sum{dp[k][0] : k ∈ i} + value[i]` (add value instead of `1`)
g19o1 "snakes" | 1d Linear | Linear | Linear | 2 | `dp(n,k)` = min sum of net sizes to catch first n groups w/ k changes | `dp(n,k)=min(dp(i,k−1)+(n−i)*max{ai+1,…,am} for i < n)` (`dp(possible previous change location) + (num groups between loc and here)*max{from prev change loc to here}`)
g18d3 "teamwork" | Linear | < | < | < | `dp[i]` = Best score up to cow `i` | `dp[i] = max{dp[i-k] + k*(max skill[i-k, k]) for 0 < k <= i}` (previous split at `i-k`)
g14d2 "feast" | Linear | Constant | Linear | 1 | `dp[i]` = Maximum fullness less than `i` without drinking water | `dp[i] = max{dp[i-1], dp[i-A]+A, dp[i-B]+B}`, then the answer is a sweep over that incorporating water drinking: `value of drinking at k = dp[k]/2`(just after drinking)`+ dp[T-dp[k]/2]`(grand total after eating more fruit)
g16o3 "248" | Linear | < | < | 2 | `dp[i][j]` = Max score after entirely collasping the range from `i` through `j` | `dp[i][j] = max{dp[i][k] + 1 for i <= k < j if dp[i][k] == dp[k+1][j]}`
DP36 tm1018 "Binary Apple Tree" (tree) | Tree | Linear | < | 2 | `dp[i][k]` = Maximum retainable apples in subtree `i` keeping `k` branches (just node `i` counts as one branch) | `dp[i][k] = max{dp[i*2][s] + dp[i*2+1][k-s-1] : 0 <= s < k} +apples[i/2][i]` (`+apples[...]` is the number of apples on the branch holding this subtree.
DP2 uva10029 "Edit Step Ladders" (longest path) | Graph | Linear | < | < (map of strings) | `dp[str]` = longest path from str | `dp[str] = max{dp[prev] : prev is an edit step of str}`, calculated during the input because input is lexographically ordered to save N^2 `strcmp`s
DP3 uva1025 "A Spy in the Metro" (abstract shortest path) | Linear | Constant | Linear | 2 | `dp[i][t]` = shortest wait to get to station `i` at time `t` | `dp[i][t] = min{dp[i][t-1], (dp[i-1][t-dist[i][t]] if exists train T : T.start_time = t-dist[0][i] && T.start_position = 0), similarly for the right side}`
DP4 uva437 "The Tower of Babylon" (abstract longest path) | Graph | Linear | < | 1 | `dp[i]` = tallest tower with block `i` at the top, where a block is a permutation of orientations | `dp[i] = max{dp[j] + height[i] for block[j] is longer and wider than block[i]}`, basically construct the graph on the fly, total N^2
DP7 uva12563 "Jin Ge Jin Qu" (multi-value knapsack rolling array) | Linear | Constant | Linear | 2 -> 1 | `dp[\_][i]` = Best value with max weight `i` with the first `\_` items (0/1 knapsack with rolling array). `dp` stores an array of pairs, since this problem asks to optimize two values. | `dp[i] = max(dp[i], { dp[i-duration[j] for item j if i >= duration[j] }), for every i`. loop through items on outer, and `i` from high to low (`for (int i=T; i>0; --i)`) because rolling array requires lower `i` to be from previous.
DP6 UVa116 "Unidirectional TSP" (but it's not TSP) | Grid Graph | Constant | Linear | 2 | `dp[i][j]` = min cost to get to row i col j. | `dp[i][j] = min{dp[i-1][j-1], dp[i][j-1], dp[i+1][j-1]}` with modulo.
501 contests/dated/2020_07_02 #3 "count coin combos" (problem not found?) | linear | constant (for this problem, based on number of coins) | linear | 2 | `dp[i][j]` = number of ways to get value `i` with maximum coin type `j` | `dp[i][j] = sum{dp[i-value[k]][k] for 1 <= k <= j}`
UVA1331 Minimax Triangulation | 2d Geometric | Linear | Linear | 2 | `dp[i][j]` = Minimax triangle size using points from `i..j` | `dp[i][j] = min{ max(dp[i][k], dp[k][j], herons(i, j, k)) : i < k < j if there are no points in the triangle (i, j, k) (concavity) }
DP10 uva1626 brackets sequence | Linear (string) | Linear | Linear | 2 | `dp[i][j] = minimum length to satisfy i..j` | `dp[i][j] = dp[i+1][j-1] if seq[i] complements seq[j], else min { dp[i][k] + dp[k][j] : i <= k <= j }`
DP15 uva1218 perfect service | Tree | Linear (each child) | Tree | 3x Linear | `dp[i][0]` = service number of subtree `i` if `i` is a server, `dp[i][1]` = service # of subtree `i` if `i` is served by a child, `dp[i][2]` = serv # of `i` if `i` is not served by a child | `dp[i][0] = sum { min{dp[k][0], dp[k][2]} for k childof i }`, `dp[i][1] = min { dp[k][0] + sum { dp[l][1] : l childo i && l != k } : k childo i } = sum { dp[k][1] : k childo i } - max { dp[k][1] - dp[k][0] : k childo i }`, `dp[i][2] = sum { dp[k][1] : k childo i }`
DP 16 uva10817 headmaster's headache | Linear | Constant | Linear | weird bitmask rep but actually 2d | `dp[i][s1][s2]` = min cost to fill given that subjects with set bits in `s1` have 1 teacher and subjects with set bits in `s2` have 2 teachers, and first `i` teachers were already considered | `dp[i][s1][s2] = min( inf if required else dp[i+1][s1][s2], dp[i+1][s1, s2 modified by classes taught by teacher[i]] )` Basically a bunch of bit twiddling for state transitions.
Knapsack 1, xjoi 7155 | Linear | Constant | Linear | 2 | can't do normal knapsack because w_i is too big, so we flip it: `dp[i][j] = minimum weight to get j value with first i items` | `dp[i][j] = min { dp[i-1][j] /* do nothing */, dp[i-1][j-v[i]]+w[i] /* take this item */ }`
[Stardew Valley](../resources/statements/zju-icpc-2020summer6F.html) | Linear | Linear | Linear | 2 | Different gift types are disjoint, so problem becomes: `dp[i][j]` = most value given `i` gifts spread over `j` villagers | `dp[i][j] = max { dp[i-1][j-k]+value[k] : 0 <= k <= min{K /* max gifts per villager */, j }`
[Teamscode Summer 2020 Hard #1 Lootcrates](../resources/statements/tc2020summer_adv_problems.pdf) | Linear | Constant | Linear | 3 | `dp[i][j][k]` = max profit after `i` days ending with `j` crates after `k` transactions | `dp[i][j][k] = max { dp[i-1][j][k] /* do nothing */, dp[i-1][j-1][k-1]-v[i] /* buy on day i */, dp[i-1][j+1][k-1]+v[i] /* sell */ }`
" Hard #2 Vacuum | 2d grid-graph | Constant | Linear | 2 | Literally the apple picking problem: `dp[i][j]` = maximum energy at (`i`, `j`) | `dp[i][j] = grid[i][j] + max { dp[i-1][j], dp[i][j-1] }`
" Hard #4 Primes | Linear | Basically partitioning into palendromes, uva11584 but with linear sieve instead of palendrome checking
" Hard #5 Juice Jam | 2x Linear | Linear | Linear | 2 | instead of 0/1 knapsack, its 0..n knapsack: `dp[i][j]` = number of ways to get `j` juice using first `i` types of boxes | `dp[i][j] = sum { dp[i-1][j-k*volume[i]] for 0 <= k <= count[i] if j - k*volume[i] >= 0 }`
[More and more](../resources/statements/zju-icpc-2020summer6C.html) | Linear | Constant | Linear | 3 | `dp[i][j][k]` = max value from 0..i but you must take i, using j multiplies, k=bool: whether this is multiplied | `dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1], 0) + val[i]; dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0], 0) + val[i]*K` take a rolling max over `dp[i][j][0], dp[i][j][1]` as you go to ensure you take something, reset to zero in the equation because negatives
poj1948 "Triangular Pastures" 2d knapsack decision | Linear | Constant | Linear | 3 w/ 1 rolling | `dp[i][j][k]` = whether you can make a triangle with side A having length `j`, side B having length `k`, with the first `i` elements | `dp[i][j][k] = dp[i-1][j][k] || dp[i-1][j-a[i][k] || dp[i-1][j][k-a[i]]`, roll over `i`, loop `j` and `k` from high to low to avoid overwriting
poj1787 "Charlies Change" maximize coins used | Linear | Log V | Linear | 2 -> 1 rolling | bounded knapsack with path reconstruction where value = 1 and weight = `c_i` for each coin type `i`, aka `dp[i][j]` = maximum coins paid using the first `i` modified coin types with total value `j`, where modified coin types are the powers of two unrolling method to get `log C_i` complexity. roll over i. | `dp[j]` at iter `i, k` = maximum number of coins used of the first `i` types in groups of `k` (`popcount(k) = 1`)
xjoi/c1609.1 apple picking | See Teamscode Summer 2020 "Hard #2 Vacuum" above.
xjoi/c1609.2 weird knapsack | TODO TODO TODO I don't understand, something about *dp[i][j] = sum of f if you have j as the sum of s using the first i cows, and then u iterate through i and then find the max i + j ignoring negatives*
xjoi/c1609.3 full cut order optimization | Linear | Linear | Binary Tree | 2 | `dp[i][j]` = min cost to combine range from `i..j` | `dp[i][j] = j-i + min{ dp[i][k] + dp[k+1][j] for i <= k < j }`
cses dp dice combinations | Scalar/Linear | Constant | Tree | 1 | `dp[i]` = max combinations to get value `i` | `dp[i] = sum { dp[i-1] + dp[i-2] + dp[i-3] + ... + dp[i-6] }`
cses dp minmizing coins, basic coin problem | Linear | Linear (over # of coins) | Linear | 1 | `dp[i]` = minimum number of coins to get value `i` | `dp[i] = min { dp[i-k] +1 for k is a valid coin value }`
cses dp coin combinations i | Linear | Linear (# of coin denominations) | Linear | 1 | `dp[i]` = number of ways to get to value `i` | `dp[i] = sum { dp[i-k] for k is a valid coin value }`
cses dp coin combinations ii | Linear | Linear (# of coin denomns, see above) | Linear | 2 -> 1 rolling | `dp[i][j]` = # of ways to get to value `j` using the first `i` denominations, this is to avoid having coins like `1, 3, 1` by having each iteration of `i` allow only the coin of type `i` | `dp[i][j] = dp[i-1][j] + sum { dp[i][j-k] for k is a coin denomination }`, rolling over `i`. Looks like unbounded knapsack...
cses dp removing digits | Linear | Logarithmic | Linear | 1 | `dp[i]` = minimum steps to clear `i` | `dp[i] = 1 + min { dp[i-k] for k is a digit in i }`
cses dp grid paths | 2d Linear | Constant | Linear | 2 (2d cell) | `dp[i][j]` = number of ways to get to coords (`i`, `j`) | `dp[i][j] = dp[i-1][j] + dp[i][j-1] if grid[i][j] is legal, else 0`
cses dp book shop aka 0/1 knapsack | see 0/1 Knapsack
cses dp array description | Linear | Constant | Tree | 2 | `dp[i][j]` = number of ways to fulfill first `i` with number `i` equal to `j` | `dp[i][j] = sum { dp[i-1][j-1] (if i > 1) + dp[i-1][j+1] (if i < M) + dp[i-1][j] }`, be careful to init the base case on `i = 1` not `i = 0`
cses dp edit distance | Linear | Constant | Linear | 2 | `dp[i][j]` = edit distance to satisfy through first `i` chars in `A` and first `j` chars in `B`, such that `i+1` and `j+1` can be matched directly next | `dp[i][j] = min { dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1] + (a[i] != b[j]) }`. Base case is `dp[0][i] = dp[i][0] = i` for all `i`
cses dp rectangle cutting | 2d | Linear | Tree | 2 | `dp[i][j]` = min steps to cut rectangle of size `i`x`j` | `dp[i][j] = min { dp[k][j] + dp[i-k][j] for 1 <= k < i, dp[i][k] + dp[i][j-k] for 1 <= k < j }`
cses dp money sums | 2d (index and value) | Constant | Linear | 2 | knapsack decision problem, where value = 1 and weight = coin value: `dp[i][j]` = whether its possible to get `j` value using the first `i` coins | `dp[i][j] = dp[i-1][j] || dp[i-1][j-v[i]`
usaco.guide PAPS 9.3 Ferry Loading (swedish OI 2013 online quals) | 4x linear | constant | 4x Tree | 4 | `dp[i][j][k][l]` = max cars with lanes having `i, j, k, l` space remaining (no need to store actual number because it is determined by the state | `dp[i][j][k][l] = max{dp[i-c][j][k][l], dp[i][j-c][k][l], ... }` where `c` is the len of the current car.
PAPS 9.4 Amusement Park (swedish OI 2012 online quals) | linear | < | < | linear + bitmask | `dp[x][i]` = min cost to visit attractions in mask `x` where the previous one was at location `1 <= i <= 2N` | `dp[x][i] = dp[x^(1<<(i%2))][k for (x>>k&1 || x>>(2*k)&1)`
PAPS 9.5 Palindrome-Free Numbers (Baltic OI 2013) | Linear (range) | constant | linear | linear + digit-enum | `dp[i][p]` = the number of palindrome-free numbers with up to `i` digits and the last two digits were `0 <= p <= 99` | `dp[i][p] = sum { dp[i-1][k*10+(p/10) for 0 <= k <= (9 or max) }` where the upper bound on `k` varies depending on whether `i` is less than the max or not.

PAPS 9.6.3 Set Cover 1 (small # of sets) | Linear (items) | Constant | Linear | bitmask | `dp[x]` = set if subsets in bitmask x are unioned | `dp[x] = dp[x-x&-x] Union subset[x&-x]`
PAPS 9.6.3 Set Cover 2 (small # of elements) | Linear (items) | Linear | Linear | Linear + bitmask   | `dp[i][x]` = minimum number of subsets to get `x` using the first `i` subsets | `dp[i][x] = min { dp[i-1][x&~a[i]], dp[i-1][x] }`
PAPS 9.6.3 Set Cover 3 (very large # of subsets) | TODO: reduce unused subsets? not fully understood
UVa108 Maximum Sum WRONG | 2d linear | constant | linear | 2 | `dp[i][j]` = maximum range sum from (0, 0) to (`i`, `j`) | `dp[i][j] = max{dp[i-1][j] + psum[the_strip_that_was_added], etc`. This is WRONG because the corner (`0, j`) may have some very large number that `dp[i-1][j]` and `dp[i][j-1]` did not consider
UVa108 Maximum Sum (correct) | 2d linear | constant | linear | 3 | `dp[l][r][i]` = maximum sum in a rect using rows `l..r` and up to column `i` | `dp[l][r][i] = psum[strip] + max(dp[l][r][i-1], 0)` aka don't take a prev rect if it was negative
TopCoder StarAdventure (3x apple picking) | 2d | constant | linear | 4 | `dp[i][j][k][l]` = max number of apples after each picker has taken `i` steps, and the first picker has `x=j`, second has `x=k`, third has `x=l` | `dp[i][j][k][l] = max { dp[i-1][j][k][l], dp[i-1][j][k][l-1], dp[i-1][j][k-1][l], dp[i-1][j][k-1][l-1], dp[i-1][j-1][k][l], ... }`
TopCoder MiniPaint inner dp (one row) | linear | constant | linear | constant + 2 + binary state | `dp[i][j][k][c=0/1]` = minimum badness to paint first `j` columns of row `i` using `k` strokes and the most recent stroke was color `0 or 1` | `dp[i][j][k][c] = min { dp[i][j-1][k][c] + (row[j] != c) /* continue prev stroke */, dp[i][j-1][k-1][!c] /* start new stroke */, j-1 /* this is the leftmost/first stroke */ }`
TopCoder MiniPaint outer dp | 2d | linear | linear | 2 | `dp[i][j]` = minimum amount of badness for first `i` rows using `j` strokes | `dp[i][j] = min { dp[i-1][k] + innerDP(i, N, j-k) for 0 <= k <= j }`
TopCoder ShortPalindromes (modified edit distance: duplicate then reverse the input string) | linear | constant | linear | 2 | `dp[i][j]` = min insertions to get first `i` chars reverse match the last `j` chars | `dp[i][j] = min { dp[i-1][j] +1, dp[i][j-1]+1, dp[i-1][j-1] if a[i] == a[N-j+1] }` ans is the min of `dp[i-1][i]`
TopCoder StripePainter (cutting sticks style range splitting) | Linear | < | < | 2 | `dp[i][j]` = min cost to paint strip from `i..j` | `dp[i][j] = min { dp[i][k] + dp[k+1][j] for i <= k < j, dp[l][r]+1 if color(i..l) == color(r..j) }` or instead of explicitly painting outer, just subtract one if `color[i] == color[j]`, (see editorials)
TopCoder Jewelry (2x count coin combos + combinatorics) | linear | constant | linear | 2 | `dp[i][j]` = number of ways to get `j` value using the first `i` coins, but twice (once with ascend sort and once with descend sort to ensure that it is `i` most valuable and `i` least valuable coins | `dp[i][j] = sum { dp[i-1][j], dp[i-1][j-v[i]] }` and then for each `i` find all `j` where both the ascend and descend exist, multiply (some modifications for duplicate jewelry values)
Kattis Poklon (sort by begin, LIS on end) | Linear | log | linear | - | LIS because if you sort by begin, then things that come later begin later, and if you LDS on end, then it ends earlier and is therefore contained.
g16d2 checklist | 2x Linear | constant | linear | 2 + enum | `dp[i][j][k = 0/1]` = min energy to visit first `i` holsteins and first `j` guernseys where FJ is currently at `j` if `k` else `i` | `dp[i][j][0] = min { dp[i-1][j][0] + dist(i-1, i), dp[i-1][j][1] + dist(j, i) }` and `dp[i][j][1] = min { dp[i][j-1][0] + dist(i, j), dp[i][j-1][1] + dist(j-1, i) }`
g17j2 hps | Linear | < | < | 2 + enum | `dp[i][j][k]` = max wins in first `i` games with `j` changes, while currently playing `0 <= k < 3` | `dp[i][j][k] = (k == a[i]) + max { dp[i-1][j][k], dp[i-1][j-1][0 <= k < 3] }`

TODO: kattis musicari, treasure diving, roller coaster fun, topcoder quicksums

> > > > > > > > > > > > >

Note on DP22: We store the basket state using a global that is updated through backtracking, which normally wouldn't work (because the basket state wouldn't necessarily be the same for each occurance of the subproblem) except that the basket state is already encoded in the frame the problem: the candies that have been through the basket can be determined by which candies have been taken, which is can be determined by how many candies have been taken from each pile. This is related to how we remember the number of cars loaded in PAPS 9.3 ferry loading.
Not considered Bitmask DP in the g21j pre-contest doc because the bitmask is an auxilary storage, not part of the DP state

Note on Tree Diameter: Another way to do the tree diameter problem is with two search traversials of the tree. Start with some node `u`, and then find the fartherst node from that node, call it `v`. Then, find the farthest node from `v` and call it `w`. The path from `v` to `w` is maxamal, because the node `v` is a "corner" aka one of the two endpoints. `v` is a corner because were it not a corner, there would be two nodes `a` and `b` that form the diameter and are corners, but because `a` and `b` are closer to `u` than `v` (that's how we found `v`), replacing the farther from `v` of `a` and `b` with `v` would result in a longer path (with the other corner being the one not replaced). Thus, `v` is a corner and `w` is the farthest from a corner, another corner.
