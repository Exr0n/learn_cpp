# DP Framing 

## Topological Structure
**Common ways to frame the problem, organized by topological structure**

- Linear
    - Each subproblem only uses the solution of one smaller subproblem, although multiple may be considered.
    - 1d
        - `dp[i]` usually represents best value up to point `i`
        - `dp[i]` sometimes represents best value "using" point `i`, because more is not always "better" or "eaiser" in some problems
        - A problem using `dp[i][j]` may be considered one dimensional if `dp[i][j+1]` is completely unrelated to `dp[i][j]`, such as when `(i, j)` represents a node in a graph
            - These problems can be thought of as one dimensional `dp[(i, j)]`
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

## Per Problem
| Problem | Structure | Frame | Equation |
|---------|-------|-----------|----------|
Number Triangle | Graph | `dp[r][c]` = Best score going down from `(r, c)` | `dp[r][c] = min(dp[r+1][c], dp[r+1][c+1])`
0/1 Knapsack | 2d Linear | `dp[i][j]` = Most value obtainable from first `i` items and having atleast `j` capacity remaining in the knapsack | `dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i])`
DP1 (UVa 10003) | 2b Tree | `dp[l][r]` = Minimum cost to cut the segment from cut `l` to `r` | `dp[l][r] = pos[r]-pos[l] + min({dp[l][k] + dp[k][r] : l < k < r})`
DP9 (UVa 11584) Subproblem | 2d Linear | `dp[l][r]` = Whether the range from `l` to `r` is a palendrome | `dp[l][r] = dp[l-1][r-1] && str[l] == str[r]`
DP9 (UVa 11584) | 1d Linear | `dp[i]` = Mininmum number of partitions to palendromify from `str[0]` to `str[i]` | `dp[i] = min({dp[j]+1 : 0 <= j < i if is_palendrome[j][i]})`
DP21 (UVa 10285) | 1d Linear | `dp[(r, c)]` = Longest decreasing sequence starting from `(r, c)` | `dp[r][c] = max({dp[(r', c')] : (r', c') is a neighbor of (r, c) if height[(r', c')] < height[(r, c)]})`
DP22* (UVa 10118) | 4d  Linear | `dp[i, j, k, l]` = Most candies obtainable using the bottom `i` candies from the first pile, `j` from the second, etc. | `dp[i, j, k, l] = max(dp[i+1, j, k, l] + whether candy of color pile1[i] was already in the basket, same for j, etc)`
DP23 (UVa 1629) | 2b Tree in 2d Decision Space | `dp[i, j, k, l]` = Minimum cost to cut cake bounded by `i <= x < k` and `j <= y < l` | `dp[i, j, k, l] = min({topCost + bottomCost + width : j < y < l if both sides have atleast one cherry} U {leftCost + rightCost + height : i < x < k if both sides have atleast one cherry})`
DP24 (UVa 1630) | 2b Tree | `dp[string]` = Minimum cost to fold `string` | `dp[string] = min({dp[string[:k]] + dp[string[k:]] : 0 < k < k.length-1}) if string is unfoldable **or** "${fold_count}(${dp[string[:prefix]]})"`
DP25 (UVa 242) | 1d Linear | `dp[i]` = Minimum number of stamps to be worth `i` money | `dp[i] = min(dp[j] + 1 : 0 <= j < i if i-j is a valid denomination of stamp)`

Note on DP22: We store the basket state using a global that is updated through backtracking, which normally wouldn't work (because the basket state wouldn't necessarily be the same for each occurance of the subproblem) except that the basket state is already encoded in the frame the problem: the candies that have been through the basket can be determined by which candies have been taken, which is can be determined by how many candies have been taken from each pile. 
