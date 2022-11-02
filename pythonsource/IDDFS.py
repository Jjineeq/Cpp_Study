class Node:
    def __init__(self, name):
        self.children = []
        self.name = name

    def addChild(self, nameList):
        for name in nameList:
            self.children.append(Node(name))
        return self

    def iterative_deepning_dfs(self, target):
        depth = 1
        bottom_reached = False
        while not bottom_reached:
            result, bottom_reached = self.iterative_deepning_dfs_helper(
                self, target, 0, depth)

            if result:
                print("Found")
                return result

            depth += 1
            print(depth, 'increased')
        return None

    def iterative_deepning_dfs_helper(self, node, target, currentDepth, maxDepth):
        print("Visiting", node.name)

        if node.name == target:
            return node, True

        if currentDepth == maxDepth:
            print("현재 최대 탐색 깊이 도달, 종료")
            if len(node.children) > 0:
                # 최하단까지 도달은 못했음
                return None, False
            else:
                return None, True

        # 자식들 모두 recursive
        bottom_reached = True
        for i in range(len(node.children)):
            result, bottom_reached_children = self.iterative_deepning_dfs_helper(
                node.children[i], target, currentDepth + 1,
                maxDepth)

            if result:
                return result, True

            bottom_reached = bottom_reached and bottom_reached_children

        return None, bottom_reached

graph = Node("A")
graph.addChild(["B", "C", "D"])
graph.children[0].addChild(["E", "F"])
graph.children[2].addChild(["G", "H"])
graph.children[0].children[1].addChild(["I", "J"])
graph.children[2].children[0].addChild(["K"])

print(graph.iterative_deepning_dfs("K"))

