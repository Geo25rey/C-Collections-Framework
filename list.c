/*
 * Copyright 1997-2007 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define LIST_IMPLEMENTATION array
#include "list.h"

#define INIT_MAX_SIZE 10
#define REALLOC_INTERVAL 10

typedef struct {
	void** array;
	int64_t size;
	int64_t maxSize;
	list_List superList;
} ArrayList;

list_List list_newList() {
	ArrayList* result = NULL;
	result = calloc(1, sizeof(ArrayList));
	assert(result != NULL);
	result->array = calloc(INIT_MAX_SIZE, sizeof(void*));
	assert(result->array != NULL);
	result->maxSize = INIT_MAX_SIZE;
	return (list_List) result;
}

bool list_delList(list_List list) {
	ArrayList* arrList = (ArrayList*) list;
	if (arrList->superList == NULL)
		free(arrList->array);
	free(arrList);
}



// Query Operations

/**
 * Returns the number of elements in this list.  If this list contains
 * more than <tt>Integer.MAX_VALUE</tt> elements, returns
 * <tt>Integer.MAX_VALUE</tt>.
 *
 * @return the number of elements in this list
 */
int64_t list_size(list_List list) {
	ArrayList* arrList = (ArrayList*) list;
	return arrList->size;
}

/**
 * Returns <tt>true</tt> if this list contains no elements.
 *
 * @return <tt>true</tt> if this list contains no elements
 */
bool list_isEmpty(list_List list) {
	ArrayList* arrList = (ArrayList*) list;
	return arrList->size == 0;
}

/**
 * Returns <tt>true</tt> if this list contains the specified element.
 * More formally, returns <tt>true</tt> if and only if this list contains
 * at least one element <tt>e</tt> such that
 * <tt>(o==null&nbsp;?&nbsp;e==null&nbsp;:&nbsp;o.equals(e))</tt>.
 *
 * @param o element whose presence in this list is to be tested
 * @return <tt>true</tt> if this list contains the specified element
 * @throws ClassCastException if the type of the specified element
 * is incompatible with this list (optional)
 * @throws NullPoint64_terException if the specified element is null and this
 * list does not permit null elements (optional)
 */
bool list_contains(list_List list, void* o) {
	ArrayList* arrList = (ArrayList*) list;
	for (int64_t i = 0; i < arrList->size; ++i)
		if (arrList->array[i] == o)
			return true;
	return false;
}

/**
 * Returns an array containing all of the elements in this list in proper
 * sequence (from first to last element).
 *
 * <p>The returned array will be "safe" in that no references to it are
 * matained by this list.  (In other words, this method must
 * allocate a new array even if this list is backed by an array).
 * The caller is thus free to modify the returned array.
 *
 * <p>This method acts as bridge between array-based and collection-based
 * APIs.
 *
 * @return an array containing all of the elements in this list in proper
 * sequence
 */
void** list_toArray(list_List list) {
	ArrayList* arrList = (ArrayList*) list;
	void** result = NULL;
	result = malloc(sizeof(void*) * arrList->size);
	assert(result != NULL);
	for (int64_t i = 0; i < arrList->size; ++i) 
		result[i] = arrList->array[i];
	return result;
}



// Modification Operations

/**
 * Appends the specified element to the end of this list (optional
 * operation).
 *
 * <p>Lists that support this operation may place limitations on what
 * elements may be added to this list.  In particular, some
 * lists will refuse to add null elements, and others will impose
 * restrictions on the type of elements that may be added.  List
 * classes should clearly specify in their documentation any restrictions
 * on what elements may be added.
 *
 * @param e element to be appended to this list
 * @return <tt>true</tt> (as specified by {@link Collection#add})
 * @throws UnsupportedOperationException if the <tt>add</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of the specified element
 * prevents it from being added to this list
 * @throws NullPoint64_terException if the specified element is null and this
 * list does not permit null elements
 * @throws IllegalArgumentException if some property of this element
 * prevents it from being added to this list
 */
bool list_add(list_List list, void* e) {
	ArrayList* arrList = (ArrayList*) list;
	if (arrList->size == arrList->maxSize) {
		void** temp = realloc(arrList->array, sizeof(void*) * (arrList->maxSize + REALLOC_INTERVAL));
		assert(temp != NULL);
		arrList->array = temp;
		arrList->maxSize += REALLOC_INTERVAL;
	}
	arrList->array[arrList->size++] = e;
	return true;
}

/**
 * Removes the first occurrence of the specified element from this list,
 * if it is present (optional operation).  If this list does not contain
 * the element, it is unchanged.  More formally, removes the element with
 * the lowest index <tt>i</tt> such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>
 * (if such an element exists).  Returns <tt>true</tt> if this list
 * contained the specified element (or equivalently, if this list changed
 * as a result of the call).
 *
 * @param o element to be removed from this list, if present
 * @return <tt>true</tt> if this list contained the specified element
 * @throws ClassCastException if the type of the specified element
 * is incompatible with this list (optional)
 * @throws NullPoint64_terException if the specified element is null and this
 * list does not permit null elements (optional)
 * @throws UnsupportedOperationException if the <tt>remove</tt> operation
 * is not supported by this list
 */
bool list_remove(list_List list, void* o) {
	ArrayList* arrList = (ArrayList*) list;
	int64_t i;
	for (i = 0; i < arrList->size; ++i)
		if (arrList->array[i] == o)
			break;
	if (i == arrList->size)
		return false;
	int64_t newSize = arrList->size - 1;
	for (; i < newSize; ++i)
		arrList->array[i] = arrList->array[i + 1];
	arrList->array[i] = NULL;
	arrList->size = newSize;
	return true;
}



// Bulk Modification Operations

/**
 * Returns <tt>true</tt> if this list contains all of the elements of the
 * specified collection.
 *
 * @param  c collection to be checked for containment in this list
 * @return <tt>true</tt> if this list contains all of the elements of the
 * specified collection
 * @throws ClassCastException if the types of one or more elements
 * in the specified collection are incompatible with this
 * list (optional)
 * @throws NullPoint64_terException if the specified collection contains one
 * or more null elements and this list does not permit null
 * elements (optional), or if the specified collection is null
 * @see #contains(void*)
 */
bool list_containsAll(list_List list, void* arr[], size_t arrLength) {
	ArrayList* arrList = (ArrayList*) list;
	bool visited[arrList->size] = {}; // initially set to false
	int64_t j; // let's not reallocate stack space for this
	for (size_t i = 0; i < arrLength; ++i) {
		for (j = 0; j < arrList->size; ++j)
			if (!visited[j]) 
				if (arrList->array[j] == arr[i]) {
					visited[j] = true;
					break;
				} 
		if (j == arrList->size)
			return false;
	}
	return true;
}

static void bulkUpdateSize(ArrayList* arrList, int64_t newSize) {
	if (newSize >= arrList->maxSize) {
		void* temp = realloc(arrList->array, sizeof(void*) * (newSize += REALLOC_INTERVAL));
		assert(temp != NULL);
		arrList->array = temp;
		arrList->maxSize = newSize;
	}
}

/**
 * Appends all of the elements in the specified collection to the end of
 * this list, in the order that they are returned by the specified
 * collection's iterator (optional operation).  The behavior of this
 * operation is undefined if the specified collection is modified while
 * the operation is in progress.  (Note that this will occur if the
 * specified collection is this list, and it's nonempty.)
 *
 * @param c collection containing elements to be added to this list
 * @return <tt>true</tt> if this list changed as a result of the call
 * @throws UnsupportedOperationException if the <tt>addAll</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of an element of the specified
 * collection prevents it from being added to this list
 * @throws NullPoint64_terException if the specified collection contains one
 * or more null elements and this list does not permit null
 * elements, or if the specified collection is null
 * @throws IllegalArgumentException if some property of an element of the
 * specified collection prevents it from being added to this list
 * @see #add(void*)
 */
bool list_addAll(list_List list, void* arr[], size_t arrLength) {
	ArrayList* arrList = (ArrayList*) list;
	int64_t newSize = arrList->size + arrLength;	
	bulkUpdateSize(arrList, newSize);
	for (int64_t i = 0; i < arrLength; ++i) 
		arrList->array[i + arrList->size] = arr[i];
	arrList->size += arrLength;
	return true;
}

/**
 * Inserts all of the elements in the specified collection int64_to this
 * list at the specified position (optional operation).  Shifts the
 * element currently at that position (if any) and any subsequent
 * elements to the right (increases their indices).  The new elements
 * will appear in this list in the order that they are returned by the
 * specified collection's iterator.  The behavior of this operation is
 * undefined if the specified collection is modified while the
 * operation is in progress.  (Note that this will occur if the specified
 * collection is this list, and it's nonempty.)
 *
 * @param index index at which to insert the first element from the
 *  specified collection
 * @param c collection containing elements to be added to this list
 * @return <tt>true</tt> if this list changed as a result of the call
 * @throws UnsupportedOperationException if the <tt>addAll</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of an element of the specified
 * collection prevents it from being added to this list
 * @throws NullPoint64_terException if the specified collection contains one
 * or more null elements and this list does not permit null
 * elements, or if the specified collection is null
 * @throws IllegalArgumentException if some property of an element of the
 * specified collection prevents it from being added to this list
 * @throws IndexOutOfBoundsException if the index is out of range
 * (<tt>index &lt; 0 || index &gt; size()</tt>)
 */
bool list_addAllAt(list_List list, int64_t index, void* arr[], size_t arrLength) {
	ArrayList* arrList = (ArrayList*) list;
	assert(index >= 0 && index <= arrList->size);
	int64_t newSize = arrList->size + arrLength;
	bulkUpdateSize(arrList, newSize);
	void** array = arrList->array;
	for (size_t i = 0; i < arrLength; ++i) {
		array[arrLength + i] = array[index + i];
		array[index + i] = arr[i];
	}
	return true;
}

/// Calculates the smallest index of the largest continuous region of items to be
/// 	removed from an ArrayList arrList
static int64_t findVisitedRegion(ArrayList* arrList, bool visited[], int64_t end) {
	for (int64_t i = end; visited[i]; --i);
	return i + 1;
}

/**
 * Removes from this list all of its elements that are contained in the
 * specified collection (optional operation).
 *
 * @param c collection containing elements to be removed from this list
 * @return <tt>true</tt> if this list changed as a result of the call
 * @throws UnsupportedOperationException if the <tt>removeAll</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of an element of this list
 * is incompatible with the specified collection (optional)
 * @throws NullPoint64_terException if this list contains a null element and the
 * specified collection does not permit null elements (optional),
 * or if the specified collection is null
 * @see #remove(void*)
 * @see #contains(void*)
 */
bool list_removeAll(list_List list, void* arr[], size_t arrLength) {
	ArrayList* arrList = (ArrayList*) list;
	bool visited[arrList->size] = {}; // initially set to false
	int64_t j; // let's not reallocate stack space for this
	for (size_t i = 0; i < arrLength; ++i) {
		for (j = 0; j < arrList->size; ++j)
			if (!visited[j]) 
				if (arrList->array[j] == arr[i]) {
					visited[j] = true;
					break;
				} 
	}
	for (int64_t i = arrList->size - 1; i >= 0; --i)
		if (visited[i]) {
			if (i == arrList->size)
				--arrList->size;
			else {
				int64_t index = findVisitedRegion(arrList, visited, i);
				int64_t newSize = arrList->size - i + index - 1;
				int64_t rmSize = i - index + 1;
				for (int64_t k = index; k < newSize; ++k)
					arrList->array[k] = arrList->array[k + rmSize];
				arrList->size = newSize;
				i = index;
			}
		}
}

/**
 * Retains only the elements in this list that are contained in the
 * specified collection (optional operation).  In other words, removes
 * from this list all of its elements that are not contained in the
 * specified collection.
 *
 * @param c collection containing elements to be retained in this list
 * @return <tt>true</tt> if this list changed as a result of the call
 * @throws UnsupportedOperationException if the <tt>retainAll</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of an element of this list
 * is incompatible with the specified collection (optional)
 * @throws NullPoint64_terException if this list contains a null element and the
 * specified collection does not permit null elements (optional),
 * or if the specified collection is null
 * @see #remove(void*)
 * @see #contains(void*)
 */
bool list_retainAll(list_List list, void* arr[], size_t arrLength) {
	ArrayList* arrList = (ArrayList*) list;
	
}

/**
 * Removes all of the elements from this list (optional operation).
 * The list will be empty after this call returns.
 *
 * @throws UnsupportedOperationException if the <tt>clear</tt> operation
 * is not supported by this list
 */
void list_clear(list_List list) {
	ArrayList* arrList = (ArrayList*) list;
	arrList->size = 0;
}



// Comparison and hashing

/**
 * Compares the specified object with this list for equality.  Returns
 * <tt>true</tt> if and only if the specified object is also a list, both
 * lists have the same size, and all corresponding pairs of elements in
 * the two lists are <i>equal</i>.  (Two elements <tt>e1</tt> and
 * <tt>e2</tt> are <i>equal</i> if <tt>(e1==null ? e2==null :
 * e1.equals(e2))</tt>.)  In other words, two lists are defined to be
 * equal if they contain the same elements in the same order.  This
 * definition ensures that the equals method works properly across
 * different implementations of the <tt>List</tt> int64_terface.
 *
 * @param o the object to be compared for equality with this list
 * @return <tt>true</tt> if the specified object is equal to this list
 */
bool list_equals(list_List list, list_List o) {
	ArrayList* arrList = (ArrayList*) list;
	ArrayList* arrList2 = (ArrayList*) o;
	if (arrList->size != arrList2->size) 
		return false;
	for (int64_t i = 0; i < arrList->size; ++i)
		if (arrList->array[i] != arrList2->array[i])
			return false;
	return true;
}



// Positional Access Operations

/**
 * Returns the element at the specified position in this list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in this list
 * @throws IndexOutOfBoundsException if the index is out of range
 * (<tt>index &lt; 0 || index &gt;= size()</tt>)
 */
void* list_get(list_List list, int64_t index) {
	ArrayList* arrList = (ArrayList*) list;
	assert(index >= 0 && index < arrList->size);
	return arrList->array[index];
}

/**
 * Replaces the element at the specified position in this list with the
 * specified element (optional operation).
 *
 * @param index index of the element to replace
 * @param element element to be stored at the specified position
 * @return the element previously at the specified position
 * @throws UnsupportedOperationException if the <tt>set</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of the specified element
 * prevents it from being added to this list
 * @throws NullPoint64_terException if the specified element is null and
 * this list does not permit null elements
 * @throws IllegalArgumentException if some property of the specified
 * element prevents it from being added to this list
 * @throws IndexOutOfBoundsException if the index is out of range
 * (<tt>index &lt; 0 || index &gt;= size()</tt>)
 */
void* list_set(list_List list, int64_t index, void* element) {
	ArrayList* arrList = (ArrayList*) list;
	assert(index >= 0 && index < arrList->size);
	void* result = arrList->array[index];
	arrList->array[index] = element;
	return result;
}

/**
 * Inserts the specified element at the specified position in this list
 * (optional operation).  Shifts the element currently at that position
 * (if any) and any subsequent elements to the right (adds one to their
 * indices).
 *
 * @param index index at which the specified element is to be inserted
 * @param element element to be inserted
 * @throws UnsupportedOperationException if the <tt>add</tt> operation
 * is not supported by this list
 * @throws ClassCastException if the class of the specified element
 * prevents it from being added to this list
 * @throws NullPoint64_terException if the specified element is null and
 * this list does not permit null elements
 * @throws IllegalArgumentException if some property of the specified
 * element prevents it from being added to this list
 * @throws IndexOutOfBoundsException if the index is out of range
 * (<tt>index &lt; 0 || index &gt; size()</tt>)
 */
void list_addAt(list_List list, int64_t index, void* element) {
	list_addAllAt(list, index, &element, 1);
}

/**
 * Removes the element at the specified position in this list (optional
 * operation).  Shifts any subsequent elements to the left (subtracts one
 * from their indices).  Returns the element that was removed from the
 * list.
 *
 * @param index the index of the element to be removed
 * @return the element previously at the specified position
 * @throws UnsupportedOperationException if the <tt>remove</tt> operation
 * is not supported by this list
 * @throws IndexOutOfBoundsException if the index is out of range
 * (<tt>index &lt; 0 || index &gt;= size()</tt>)
 */
void* list_removeAt(list_List list, int64_t index) {
	ArrayList* arrList = (ArrayList*) list;
	assert(index >= 0 && index < arrList->size);
	void* result = arrList->array[index];
	--arrList->size;
	for (int64_t i = index; i < arrList->size; ++i)
		arrList->array[i] = arrList->array[i + 1];
	return result;
}



// Search Operations

/**
 * Returns the index of the first occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the lowest index <tt>i</tt> such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the first occurrence of the specified element in
 * this list, or -1 if this list does not contain the element
 * @throws ClassCastException if the type of the specified element
 * is incompatible with this list (optional)
 * @throws NullPoint64_terException if the specified element is null and this
 * list does not permit null elements (optional)
 */
int64_t list_indexOf(list_List list, void* o) {
	ArrayList* arrList = (ArrayList*) list;
	for (int64_t i = 0; i < arrList->size; ++i)
		if (arrList->array[i] == o)
			return i;
	return -1;
}

/**
 * Returns the index of the last occurrence of the specified element
 * in this list, or -1 if this list does not contain the element.
 * More formally, returns the highest index <tt>i</tt> such that
 * <tt>(o==null&nbsp;?&nbsp;get(i)==null&nbsp;:&nbsp;o.equals(get(i)))</tt>,
 * or -1 if there is no such index.
 *
 * @param o element to search for
 * @return the index of the last occurrence of the specified element in
 * this list, or -1 if this list does not contain the element
 * @throws ClassCastException if the type of the specified element
 * is incompatible with this list (optional)
 * @throws NullPoint64_terException if the specified element is null and this
 * list does not permit null elements (optional)
 */
int64_t list_lastIndexOf(list_List list, void* o) {
	ArrayList* arrList = (ArrayList*) list;
	for (int64_t i = arrList->size - 1; i >= 0; --i)
		if (arrList->array[i] == o)
			return i;
	return -1;
}



// View

/**
 * Returns a view of the portion of this list between the specified
 * <tt>fromIndex</tt>, inclusive, and <tt>toIndex</tt>, exclusive.  (If
 * <tt>fromIndex</tt> and <tt>toIndex</tt> are equal, the returned list is
 * empty.)  The returned list is backed by this list, so non-structural
 * changes in the returned list are reflected in this list, and vice-versa.
 * The returned list supports all of the optional list operations supported
 * by this list.<p>
 *
 * This method eliminates the need for explicit range operations (of
 * the sort that commonly exist for arrays).  Any operation that expects
 * a list can be used as a range operation by passing a subList view
 * instead of a whole list.  For example, the following idiom
 * removes a range of elements from a list:
 * <pre>
 *  list.subList(from, to).clear();
 * </pre>
 * Similar idioms may be constructed for <tt>indexOf</tt> and
 * <tt>lastIndexOf</tt>, and all of the algorithms in the
 * <tt>Collections</tt> class can be applied to a subList.<p>
 *
 * The semantics of the list returned by this method become undefined if
 * the backing list (i.e., this list) is <i>structurally modified</i> in
 * any way other than via the returned list.  (Structural modifications are
 * those that change the size of this list, or otherwise perturb it in such
 * a fashion that iterations in progress may yield incorrect results.)
 *
 * @param fromIndex low endpoint64_t (inclusive) of the subList
 * @param toIndex high endpoint64_t (exclusive) of the subList
 * @return a view of the specified range within this list
 * @throws IndexOutOfBoundsException for an illegal endpoint64_t index value
 * (<tt>fromIndex &lt; 0 || toIndex &gt; size ||
 * fromIndex &gt; toIndex</tt>)
 */
list_List list_subList(list_List list, int64_t fromIndex, int64_t toIndex) {
	ArrayList* arrList = (ArrayList*) list;
	assert(fromIndex >= 0 && toIndex <= arrList->size && toIndex >= fromIndex);
	ArrayList* result = NULL;
	result = malloc(sizeof(ArrayList));
	result->array = arrList->array + fromIndex;
	result->size = fromIndex - toIndex + 1;
	result->maxSize = arrList->maxSize - fromIndex + 1;
	result->superList = list;
	return (list_List) result;
}

