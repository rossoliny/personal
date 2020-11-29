
/*************************************************************************
   LAB 1                                                                

    Edit this file ONLY!

*************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "bst.h"
#include "dns.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef Node* Tree;
typedef Tree* TreeArray;

static TreeArray trees = NULL;
static unsigned int trees_capacity = 0; // track the actuall capacity of tree array
static DNSHandle trees_size = 0; // track number of trees

DNSHandle InitDNS() {
    ++trees_size;
    // if TreeArray has no free space then reallocate memory and copy data from previous memory
    if (trees_capacity <= trees_size || trees_size-1 == 0) {
        Node** prev = trees;
        // Dont reallocate evertime. Just reserve more space for future. 
        int newCapacity = trees_size-1 == 0 ? 1 : trees_size * 2; 
        trees = calloc(newCapacity, sizeof(Node*));
        trees_capacity = newCapacity;
        trees[trees_size - 1] = bst_init();
        // copy data
        for (unsigned int i = 0; i < trees_size - 1; i++) {
            trees[i] = prev[i];
        }
        free(prev);
    }
    else {
        trees[trees_size - 1] = bst_init();
    }
    return trees_size;
}

void LoadHostsFile(DNSHandle hDNS, const char *hostsFilePath) {
    // if hDNS is out of bounds
    if (hDNS <= 0 || hDNS > trees_size){
        return;
    }
    // load file
    FILE *file = fopen(hostsFilePath, "r");
    if (file != NULL) {
        unsigned int a, b, c, d;
        char *hostName = NULL;

        // allocate temporary memory for data from file
        hostName = calloc(255, sizeof(char));
        while (fscanf(file, "%d.%d.%d.%d %s", &a, &b, &c, &d, hostName) != EOF) { // read from file until eof
            IPADDRESS ip = (a << 24) + (b << 16) + (c << 8) + d;
            bst_insert(trees[hDNS - 1], hostName, ip);
        }
        free(hostName);
    }
    fclose(file);
}

IPADDRESS DnsLookUp(DNSHandle hDNS, const char *hostName) {
    if (hDNS <= 0 || hDNS > trees_size) {
        // hDNS out of bounds
        return INVALID_IP_ADDRESS;
    }
    return bst_find(trees[hDNS - 1], hostName)->ip;
}

// must shut donw only one dns server
// currentry shuts down all servers
void ShutdownDNS(DNSHandle hDNS) {
    if (trees == NULL) {
        return;
    }
    for (unsigned int i = 0; i < trees_capacity; i++) {
        bst_destruct(trees[i]);
    }
    free(trees);
    trees = NULL;
    trees_capacity = 0;
    trees_size = 0;

    // shutdown only specified handle
    /*
    if (trees == NULL) {
        return;
    }
    Node* res = bst_destruct(servers[hDNS - 1]);
    if (res) {
        // TODO: error, couldnt delete
    }
    servers[hDNS - 1] = NULL;
    trees_n--;
    */
}

