//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     IVAN BOBROV <xbobro01@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author IVAN BOBROV
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//
class NonEmptyTree : public ::testing::Test {
    protected:

    virtual void SetUp() {
        int values[] = { 1, 2, 5, 7, 8, 11};

        for(int i = 0; i < 6; ++i)
            non_empty_tree.InsertNode(values[i]);
    }

    BinaryTree non_empty_tree;
};

class EmptyTree : public ::testing::Test {
    protected:

    BinaryTree empty_tree;
};

class TreeAxioms : public ::testing::Test {
    protected:

    virtual void SetUp() {
        int values[] = { 1, 2, 5, 7, 8, 11, 14};

        for(int i = 0; i < 7; ++i)
            axiome_tree.InsertNode(values[i]);
    }

    BinaryTree axiome_tree;
};

TEST_F(EmptyTree, InsertNode) {
    // init helpfull data structures
    struct Node_t *null_root = NULL;
    std::pair<bool, struct Node_t*> inserted_node1;
    std::pair<bool, struct Node_t*> inserted_node2;
    std::pair<bool, struct Node_t*> inserted_node3;
   // std::pair<bool, struct Node_t*> inserted_node4;

    // check tree existense
    ASSERT_NO_THROW(empty_tree.GetRoot());
    EXPECT_EQ(null_root, empty_tree.GetRoot());

    // adding new node
    ASSERT_NO_THROW(inserted_node1 = empty_tree.InsertNode(2));
    EXPECT_EQ(true, inserted_node1.first);
    EXPECT_EQ(2, inserted_node1.second->key);
    EXPECT_EQ(BinaryTree::BLACK, inserted_node1.second->color);

    // adding already existed node
    ASSERT_NO_THROW(inserted_node2 = empty_tree.InsertNode(2));
    EXPECT_EQ(false, inserted_node2.first);
    EXPECT_EQ(inserted_node1.second, inserted_node2.second);

    // adding second node
    ASSERT_NO_THROW(inserted_node3 = empty_tree.InsertNode(1));
    EXPECT_EQ(true, inserted_node3.first);
    EXPECT_EQ(1, inserted_node3.second->key);
    EXPECT_EQ(BinaryTree::RED, inserted_node3.second->color);
    // TODO: adding third node, adding several nodes ?
}

TEST_F(EmptyTree, FindNode) {
    Node_t *null_node = NULL;
    Node_t *founded_node = NULL;

    // adding nodes
    ASSERT_NO_THROW(empty_tree.InsertNode(2));
    ASSERT_NO_THROW(empty_tree.InsertNode(1));

    // search for existing node (root)
    ASSERT_NO_THROW(founded_node = empty_tree.FindNode(2));
    EXPECT_EQ(2, founded_node->key);
    ASSERT_NO_THROW(founded_node = empty_tree.FindNode(1));
    EXPECT_EQ(1, founded_node->key);

    // searching for no existing node
    ASSERT_NO_THROW(founded_node = empty_tree.FindNode(-4));
    EXPECT_EQ(null_node, founded_node);
    
    ASSERT_NO_THROW(founded_node = empty_tree.FindNode(4));
    EXPECT_EQ(null_node, founded_node);
}

TEST_F(EmptyTree, DeleteNode) {
    Node_t *null_node = NULL;
    bool succeed = false;
    // adding nodes
    ASSERT_NO_THROW(empty_tree.InsertNode(2));
    ASSERT_NO_THROW(empty_tree.InsertNode(1));
    ASSERT_NO_THROW(empty_tree.InsertNode(3));

    // removing existing nodes
    ASSERT_NO_THROW(succeed = empty_tree.DeleteNode(1));
    EXPECT_EQ(true, succeed);

    ASSERT_NO_THROW(succeed = empty_tree.DeleteNode(3));
    EXPECT_EQ(true, succeed);

    // removing no existing nodes
    ASSERT_NO_THROW(succeed = empty_tree.DeleteNode(-4));
    EXPECT_EQ(false, succeed);

    ASSERT_NO_THROW(succeed = empty_tree.DeleteNode(4));
    EXPECT_EQ(false, succeed);
}

TEST_F(NonEmptyTree, InsertNode) {
    struct Node_t *root_before_insert = NULL;
    struct Node_t *root_after_insert = NULL;
    struct Node_t *null_root = NULL;
    std::pair<bool, struct Node_t*> inserted_node1;
    std::pair<bool, struct Node_t*> inserted_node2;
    std::pair<bool, struct Node_t*> inserted_node3;

    // check tree existense
    ASSERT_NO_THROW(non_empty_tree.GetRoot());
    EXPECT_NE(null_root, non_empty_tree.GetRoot());

    // adding new node
    ASSERT_NO_THROW(inserted_node1 = non_empty_tree.InsertNode(14));
    EXPECT_EQ(true, inserted_node1.first);
    EXPECT_EQ(14, inserted_node1.second->key);
    EXPECT_EQ(BinaryTree::RED, inserted_node1.second->color);
    ASSERT_NO_THROW(root_before_insert = non_empty_tree.GetRoot());

    // adding already existed node
    ASSERT_NO_THROW(inserted_node2 = non_empty_tree.InsertNode(14));
    EXPECT_EQ(false, inserted_node2.first);
    EXPECT_EQ(inserted_node1.second, inserted_node2.second);

    // adding second node
    ASSERT_NO_THROW(inserted_node3 = non_empty_tree.InsertNode(15));
    EXPECT_EQ(true, inserted_node3.first);
    EXPECT_EQ(15, inserted_node3.second->key);
    EXPECT_EQ(BinaryTree::RED, inserted_node3.second->color);

    // chech if root was changed
    ASSERT_NO_THROW(root_after_insert = non_empty_tree.GetRoot());
    EXPECT_NE(root_before_insert->key, root_after_insert->key);

    // check if second node was conected propertly
    EXPECT_EQ(11, inserted_node1.second->pParent->key);
    EXPECT_EQ(inserted_node3.second->pParent, inserted_node1.second);
    EXPECT_EQ(BinaryTree::RED, inserted_node3.second->color); 
}

TEST_F(NonEmptyTree, FindNode) {
    Node_t *null_node = NULL;
    Node_t *founded_node1 = NULL;
    Node_t *founded_node2 = NULL;

    // adding new nodes
    ASSERT_NO_THROW(non_empty_tree.InsertNode(14));
    ASSERT_NO_THROW(non_empty_tree.InsertNode(15));

    // search for existing node (root)
    ASSERT_NO_THROW(founded_node1 = non_empty_tree.FindNode(14));
    EXPECT_EQ(14, founded_node1->key);
    ASSERT_NO_THROW(founded_node2 = non_empty_tree.FindNode(15));
    EXPECT_EQ(15, founded_node2->key);

    // check if founded nodes were placed in the write order
    EXPECT_EQ(founded_node1, founded_node2->pParent);

    // searching for no existing node
    ASSERT_NO_THROW(founded_node1 = non_empty_tree.FindNode(-20));
    EXPECT_EQ(null_node, founded_node1);
    ASSERT_NO_THROW(founded_node1 = non_empty_tree.FindNode(20));
    EXPECT_EQ(null_node, founded_node1);
}

TEST_F(NonEmptyTree, DeleteNode) {
    Node_t *null_node = NULL;
    Node_t *removed_node = NULL;
    bool succeed = false;

    // removing existing nodes
    ASSERT_NO_THROW(succeed = non_empty_tree.DeleteNode(1));
    EXPECT_EQ(true, succeed);
    ASSERT_NO_THROW(removed_node = non_empty_tree.FindNode(1));
    EXPECT_EQ(null_node, removed_node);

    ASSERT_NO_THROW(succeed = non_empty_tree.DeleteNode(11));
    EXPECT_EQ(true, succeed);
    ASSERT_NO_THROW(removed_node = non_empty_tree.FindNode(11));
    EXPECT_EQ(null_node, removed_node);

    // removing no existing nodes
    ASSERT_NO_THROW(succeed = non_empty_tree.DeleteNode(-20));
    EXPECT_EQ(false, succeed);
    ASSERT_NO_THROW(succeed = non_empty_tree.DeleteNode(20));
    EXPECT_EQ(false, succeed);

}

TEST_F(TreeAxioms, FirstAxiom) {
    std::vector<Node_t*> leaf_nodes;

    // try to get leafs
    ASSERT_NO_THROW(axiome_tree.GetLeafNodes(leaf_nodes));
  
    // check leafs quantity
    char leaf_count = leaf_nodes.size();
    ASSERT_EQ(8, leaf_count);

    // check if every leaf is black
    for(int i = 0; i < leaf_count; i++) {
        Node_t *leaf = leaf_nodes[i];
        EXPECT_EQ(BinaryTree::BLACK, leaf->color);
    }
}

TEST_F(TreeAxioms, SecondAxiom) {
    std::vector<Node_t*> all_nodes;
    axiome_tree.GetAllNodes(all_nodes);
    char node_count =  all_nodes.size();

    // chech if black nodes were inherited from red one 
    for(int i = 0; i < node_count; i++) {
        if(all_nodes[i]->color == BinaryTree::RED) {
            ASSERT_EQ(BinaryTree::BLACK, all_nodes[i]->pLeft->color);
            ASSERT_EQ(BinaryTree::BLACK, all_nodes[i]->pRight->color);
        }
    }
}

TEST_F(TreeAxioms, ThirdAxiom) {
    std::vector<Node_t*> leaf_nodes;
    // try to get leafs
    ASSERT_NO_THROW(axiome_tree.GetLeafNodes(leaf_nodes));
  
    // check leafs quantity
    char leaf_count = leaf_nodes.size();
    ASSERT_EQ(8, leaf_count);

    // get number of black nodes
    Node_t *tmp_node = leaf_nodes[1];
    int black_node_number = 0;
    while(tmp_node != NULL){
            if(tmp_node->color == BinaryTree::BLACK) {
                black_node_number++;
            }
            tmp_node = tmp_node->pParent; 
    }
    
    // check if every way from leafs to root contains same quantity of black nodes
    int black_node_count = 0;
    for(int i = 0; i < leaf_count; i++) {
        tmp_node = leaf_nodes[i];
        while(tmp_node != NULL){
            if(tmp_node->color == BinaryTree::BLACK) {
                black_node_count++;
            }
            tmp_node = tmp_node->pParent; 
        }
        EXPECT_EQ(black_node_number, black_node_count);
        black_node_count = 0;
    }

}
/*** Konec souboru black_box_tests.cpp ***/
