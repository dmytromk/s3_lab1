#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "LinkedStructs.h"

#include "Trees.h"
#include "doctest.h"
#include "Dice.h"

#include <iostream>

TEST_CASE("testing the general tree")
{
    tree::MultTree<int> mult_tree;
    REQUIRE(mult_tree.head == nullptr);

    SUBCASE("adding the element to empty tree changes its head")
    {
        mult_tree.add(mult_tree.head, 1);
        CHECK(mult_tree.head->children.size() == 0);
        CHECK(mult_tree.head->parent == nullptr);
    }

    SUBCASE("deletion the element from the empty tree doesn't do anything")
    {
        mult_tree.deleteAllChildren(mult_tree.head);

        CHECK(mult_tree.head == nullptr);
    }

    SUBCASE("deletion the head's children changes it")
    {
        mult_tree.add(mult_tree.head, 1);
        mult_tree.deleteAllChildren(mult_tree.head);

        CHECK(mult_tree.head->children.size() == 0);
    }

    SUBCASE("adding many elements")
    {
        mult_tree.add(mult_tree.head, 1);
        CHECK(mult_tree.head->key == 1);

        for (int i = 0; i < 4; i++)
        {
            mult_tree.add(mult_tree.head, i + 2);
            CHECK(mult_tree.head->children[i]->key == i + 2);
            CHECK(mult_tree.head->children[i]->parent == mult_tree.head);
        }

        for (int i = 0; i < 4; i++)
        {
            mult_tree.add(mult_tree.head->children[i], i + 6);
            CHECK(mult_tree.head->children[i]->children[0]->key == i + 6);
            CHECK(mult_tree.head->children[i]->children[0]->parent == mult_tree.head->children[i]);

            CHECK(mult_tree.searchBreadthFirst(i + 6, mult_tree.head) == mult_tree.head->children[i]->children[0]);
            CHECK(mult_tree.searchInOrder(i + 6, mult_tree.head) == mult_tree.head->children[i]->children[0]);
            CHECK(mult_tree.searchPostOrder(i + 6, mult_tree.head) == mult_tree.head->children[i]->children[0]);
            CHECK(mult_tree.searchPreOrder(i + 6, mult_tree.head) == mult_tree.head->children[i]->children[0]);
        }

        SUBCASE("delete the head's children")
        {
            mult_tree.deleteAllChildren(mult_tree.head);
            CHECK(mult_tree.head->children.size() == 0);
        }

        SUBCASE("delete the childless head chidren")
        {
            for (int i = 0; i < 4; i++)
            {
                mult_tree.deleteAllChildren(mult_tree.head->children[i]->children[0]);
                CHECK(mult_tree.head->children[i]->children[0]->children.size() == 0);
                CHECK(mult_tree.head->children[i]->children[0]->parent == mult_tree.head->children[i]);
            }
        }

        SUBCASE("delete by the child index")
        {
            for (int i = 0; i < 4; i++)
            {
                mult_tree.deleteByNodeIdx(mult_tree.head, 0);
                CHECK(mult_tree.head->children.size() == 3-i);
            }
        }

        SUBCASE("delete by the key")
        {
            SUBCASE("promote no node and delete all the children")
            {
                SUBCASE("the node is the head")
                {
                    mult_tree.deleteByNodeKey(1, 0);
                    CHECK(mult_tree.head == nullptr);
                }

                SUBCASE("the node isn't the head")
                {
                    mult_tree.deleteByNodeKey(2, 0);
                    CHECK(mult_tree.head->children.size() == 3);
                }
            }

            SUBCASE("node has only the one child")
            {
                mult_tree.deleteByNodeKey(2, 1);
                CHECK(mult_tree.head->children[0]->key == 6);
                CHECK(mult_tree.head->children[0]->parent == mult_tree.head);

            }

            SUBCASE("promote all the children")
            {
                mult_tree.add(mult_tree.head->children[0], 10);
                SUBCASE("the node is the head")
                {
                    auto temp = mult_tree.head->children[0];
                    mult_tree.deleteByNodeKey(1, -1);
                    CHECK(mult_tree.head == temp);
                    CHECK(temp->parent == nullptr);
                    CHECK(temp->children.size() == 5);
                }

                SUBCASE("the node isn't the head")
                {
                    mult_tree.deleteByNodeKey(2, -1);
                    for (int i = 0; i < 5; i++)
                    {
                        CHECK(mult_tree.head->children[i]->parent == mult_tree.head);
                    }
                    for (int i = 3; i < 5; i++)
                    {
                        CHECK(mult_tree.head->children[i]->children.size() == 0);
                    }
                }
            }

            SUBCASE("promote the n-th node")
            {
                mult_tree.add(mult_tree.head->children[0], 10);
                SUBCASE("the node is the head")
                {
                    auto temp = mult_tree.head->children[2];
                    mult_tree.deleteByNodeKey(1, 3);
                    CHECK(mult_tree.head == temp);
                    CHECK(temp->parent == nullptr);
                    CHECK(temp->children.size() == 4);
                }

                SUBCASE("the node isn't the head")
                {
                    auto temp = mult_tree.head->children[0]->children[1];
                    mult_tree.deleteByNodeKey(2, 2);
                    CHECK(mult_tree.head->children[0] == temp);
                    CHECK(mult_tree.head->children[0]->key == 10);
                    CHECK(mult_tree.head->children[0]->parent == mult_tree.head);
                }
            }
        }
    }
}

TEST_CASE("testing the binary tree")
{
    tree::BinTree<int> bin_tree;
    REQUIRE(bin_tree.head == nullptr);

    SUBCASE("deletion the head's children changes its children pointers")
    {
        bin_tree.add(1, bin_tree.head);

        bin_tree.add(2, bin_tree.head);
        CHECK(bin_tree.head->left->parent == bin_tree.head);

        bin_tree.add(3, bin_tree.head);
        CHECK(bin_tree.head->right->parent == bin_tree.head);

        bin_tree.deleteByNode(bin_tree.head);

        CHECK(bin_tree.head == nullptr);
    }

    for (int i = 0; i < 9; i++)
        bin_tree.add(i, bin_tree.head);

    SUBCASE("search check")
    {
        for (int i = 0; i < 9; i++)
        {
            CHECK(bin_tree.searchBreadthFirst(i, bin_tree.head)->key == i);
            CHECK(bin_tree.searchInOrder(i, bin_tree.head)->key == i);
            CHECK(bin_tree.searchPostOrder(i, bin_tree.head)->key == i);
            CHECK(bin_tree.searchPreOrder(i, bin_tree.head)->key == i);
        }
    }
    
    SUBCASE("delete by node")
    {
        SUBCASE("delete head")
        {
            bin_tree.deleteByNode(bin_tree.head);
            CHECK(bin_tree.head == nullptr);
        }

        SUBCASE("delete normal element")
        {
            bin_tree.deleteByNode(bin_tree.head->left);
            CHECK(bin_tree.head->left == nullptr);
        }
    }

    SUBCASE("delete by key")
    {
        SUBCASE("delete head")
        {
            bin_tree.deleteByKey(0, bin_tree.head);
            CHECK(bin_tree.head == nullptr);
        }

        SUBCASE("delete normal element")
        {
            bin_tree.deleteByKey(1, bin_tree.head);
            CHECK(bin_tree.head->left == nullptr);

            bin_tree.deleteByKey(2, bin_tree.head);
            CHECK(bin_tree.head->right == nullptr);
        }
    }
}

TEST_CASE("testing the binary search tree")
{
    tree::BinSearchTree<int> bin_search_tree;
    REQUIRE(bin_search_tree.head == nullptr);

    SUBCASE("deletion the head's children changes its children pointers")
    {
        bin_search_tree.add(1, bin_search_tree.head);

        bin_search_tree.add(2, bin_search_tree.head);
        CHECK(bin_search_tree.head->right->parent == bin_search_tree.head);

        bin_search_tree.add(3, bin_search_tree.head);
        CHECK(bin_search_tree.head->right->right->parent->parent == bin_search_tree.head);

        bin_search_tree.add(0, bin_search_tree.head);
        CHECK(bin_search_tree.head->left->parent == bin_search_tree.head);

        bin_search_tree.add(-1, bin_search_tree.head);
        CHECK(bin_search_tree.head->left->left->parent->parent == bin_search_tree.head);

        bin_search_tree.deleteByNode(bin_search_tree.head);

        CHECK(bin_search_tree.head == nullptr);
    }

    SUBCASE("minimal key check")
    {
        for (int i = 0; i > -5; i--)
            bin_search_tree.add(i, bin_search_tree.head);
        CHECK(bin_search_tree.minKeyNode(bin_search_tree.head)->key == -4);
    }

    SUBCASE("delete by key")
    {
        for (int i = 0; i < 3; i++)
            bin_search_tree.add(i, bin_search_tree.head);

        for (int i = 0; i > -3; i--)
            bin_search_tree.add(i, bin_search_tree.head);

        SUBCASE("delete element with left child")
        {
            bin_search_tree.deleteByNodeKey(-1, bin_search_tree.head);
            CHECK(bin_search_tree.head->left->key == -2);
        }

        SUBCASE("delete element with right child")
        {
            bin_search_tree.deleteByNodeKey(1, bin_search_tree.head);
            CHECK(bin_search_tree.head->right->key == 2);
        }

        SUBCASE("delete element with both children")
        {
            bin_search_tree.deleteByKey(1, bin_search_tree.head);
            bin_search_tree.add(10, bin_search_tree.head);
            bin_search_tree.add(5, bin_search_tree.head);
            bin_search_tree.add(15, bin_search_tree.head);
            bin_search_tree.deleteByNodeKey(10, bin_search_tree.head);
            CHECK(bin_search_tree.head->right->key == 15);
            CHECK(bin_search_tree.head->right->left->key == 5);
        }
    }
}

TEST_CASE("testing the random dice")
{
    const int N = 20;
    gambling::Dice dice(N);
    SUBCASE("testing random weight distribution")
    {
        dice.randomWeightDistribution();
        double x = 0;
        for (auto i : dice.weight_distribution)
        {
            x += i;
            std::cout << i << "\n";
        }
        std::cout << x;
        std::cout << "\n__________________________________\n\n";
    }
}

TEST_CASE("testing the dice sers")
{
    gambling::Dice dice1(2);
    dice1.weight_distribution = { 0.5, 0.5 };
    CHECK(dice1.amount == 2);

    gambling::Dice dice2(4);
    dice2.weight_distribution = { 0.2, 0.4, 0.4, 0.2 };
    CHECK(dice2.amount == 4);

    gambling::DiceSet dice_set;
    dice_set.add(dice1);
    dice_set.add(dice2);
    CHECK(dice_set.dices.size() == 2);

    SUBCASE("sum and their probabilitues")
    {
        dice_set.countSums();
        for (const auto& v : dice_set.probabilityDictionary)
        {
            std::cout << v.first << " has probability of " << v.second << "\n";
        }
    }
}

TEST_CASE("testing the linked structure")
{
    linked::Deque<int> deque;
    REQUIRE(deque.empty() == true);
    REQUIRE(deque.size() == 0);
    REQUIRE(deque.head == nullptr);
    REQUIRE(deque.tail == nullptr);

    
	deque.pushBack(1);
	CHECK(deque.head->value == 1);
	CHECK(deque.tail->value == 1);
	deque.pushBack(2);
	CHECK(deque.head->value == 1);
	CHECK(deque.head->next == deque.tail);
	CHECK(deque.tail->value == 2);
	CHECK(deque.tail->prev == deque.head);

	CHECK(deque.top() == 1);
	CHECK(deque.back() == 2);

	deque.pushBack(3);

    deque.popTop();
    CHECK(deque.head->value == 2);

    deque.popBack();
    CHECK(deque.head->value == deque.tail->value);

}