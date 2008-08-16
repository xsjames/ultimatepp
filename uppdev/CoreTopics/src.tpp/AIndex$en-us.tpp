topic "AIndex";[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;*@(64)2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[a83;*R6 $$3,0#31310162474203024125188417583966:caption]
[l288;i1121;b17;O9;~~~.1408;2 $$4,0#10431211400427159095818037425705:param]
[i448;a25;kKO9;*@(64)2 $$5,0#37138531426314131252341829483370:item]
[*+117 $$6,6#14700283458701402223321329925657:header]
[l288;a17;*1 $$7,7#70004532496200323422659154056402:requirement]
[{_}%EN-US 
[s5;K@0 [%00-00@(64) template_<][%00-00@(0.0.255) class][%00-00@(64) _][%00-00@4 T][%00-00@(64) ,
 ][%00-00@(0.0.255) class][%00-00@(64) _][%00-00@4 V][%00-00@(64) , ][%00-00@(0.0.255) clas
s][%00-00@(64) _][%00-00@4 HashFn][%00-00@(64) >__][%00-00@(0.0.255) class][%00-00@(64) _][%00-00 A
Index]&]
[s0;t292;* [* class ]AIndex&]
[s0; &]
[s0; [*C@4 T]-|Type of elements to store. T must satisfy requirements 
for container flavor identified by parameter V and must have 
[*C operator`=`=] defined.&]
[s0; [*C@4 V]-|Basic random access container.&]
[s0; [*C@4 HashFn]-|Hashing class. Must have defined [*C unsigned operator()(const 
T`& x)] method returning hash value for elements.&]
[s0; This template class adds associative capabilities to basic random 
access containers, forming flavors of Index. It is used as base 
class for concrete index flavors, [* Index] and [* ArrayIndex].&]
[s0; It allows adding elements at the end of sequence in constant 
amortized time like basic random container. Additionally, it 
also allows fast retrieval of a position of the element with 
specified value. Hashing is used for this operation. AIndex stores 
hash`-values of elements, so it has no sense to cache them externally.&]
[s0; Building of internal hash maps of AIndex is always deferred 
till search operation. This effectively avoids unneeded remapping 
if large number of elements is added.&]
[s0; Removing elements from an AIndex causes an interesting problem. 
While it is possible to simply remove (or insert) an element 
at a specified position, such operation has to move a lot of 
elements and also scratches internal hash maps. Thus removing 
elements this way is slow, especially when combined with searching.&]
[s0; The solution for this problem is [*/ unlinking] of elements. Unlinked 
elements are not removed from index, but they are [*/ ignored][/  
]by search operations. Unlinking is a simple, constant time, 
fast operation. Further, it is possible to place an element at 
the first available unlinked position (rather than to the end 
of sequence) using the [* Put] method, reusing unlinked position 
in short constant time.&]
[s0; The only problem of unlinking is that it breaks the so`-called 
[* multi`-key ordering]. This term means that if there are more 
elements with the same value in the index and they are iterated 
through using the FindNext method, their positions (got as the 
result of Find and subsequent FindNext methods) are in ascending 
order. The problem is that it is impossible to implement placing 
elements at unlinked positions in short time while preserving 
this ordering. On the other hand, usage scenarios for indexes 
show that need for unlinking elements and multi`-key ordering 
is almost always disjunct. For the rest of the cases, it is always 
possible to restore ordering by the [* Reindex] or the [* Sweep] 
method.&]
[s0; Like any other NTL container, AIndex is [*/^topic`:`/`/Core`/srcdoc`/Moveable`$en`-us^ m
oveable][*/  ]type with [*/^topic`:`/`/Core`/srcdoc`/Moveable`$en`-us^ pick 
and optional deep copy] transfer semantics, although these features 
are more important in derived concrete index flavors.&]
[s0; Members&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Add][%00-00 (][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T
][%00-00 `&_][%00-00@3 x][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 `_hash][%00-00 )
]&]
[s2; Adds a new element with a precomputed hash value.The precomputed 
hash value must be the same as the hash value that would be the 
result of HashFn. The benefit of this variant is that sometimes 
you can compute hash`-value as the part of an other process, 
like fetching strings from an input stream.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 x]-|Element to add.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Add][%00-00 (][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T
][%00-00 `&_][%00-00@3 x][%00-00 )]&]
[s2; Adds a new element to AIndex.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 x]-|Element to add.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 Find][%00-00@(64) (][%00-00 const][%00-00@(64) _
][%00-00@4 T][%00-00@(64) `&_][%00-00@3 x][%00-00@(64) , ][%00-00 unsigned][%00-00@(64) _][%00-00@3 `_
hash][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the first element with the specified 
value in AIndex, using a precomputed hash value. The precomputed 
hash value must be the same as the hash value that would be result 
of HashFn. If multi`-key ordering is not broken and more than 
one element with the same value exists in AIndex, the lowest 
position is retrieved. If the specified value does not exist 
in AIndex, a negative number is returned. Unlinked elements are 
ignored.&]
[s4; [*C@3 x]-|Element to find.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the element or negative value if 
value is not in AIndex.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 Find][%00-00@(64) (][%00-00 const][%00-00@(64) _
][%00-00@4 T][%00-00@(64) `&_][%00-00@3 x][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the first element with the specified 
value in AIndex. If multi`-key ordering is not broken and more 
than one element with the same value exists in AIndex, lowest 
position is retrieved. If the specified value does not exist 
in AIndex, a negative number is returned. Unlinked elements are 
ignored.&]
[s4; [*C@3 x]-|Element to find.&]
[s4; [*/ Return value]-|Position of the element or negative value if 
value is not in AIndex.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 FindNext][%00-00@(64) (][%00-00 int][%00-00@(64) _
][%00-00@3 i][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the next element with the same value 
as the element at specified position. If multi`-key ordering 
is not broken and more than one element with that value exists 
in AIndex, the lowest position greater than specified one is 
retrieved, so positions returned by subsequent calls to FindNext 
are in ascending order. When there are no more elements with 
the required value, a negative number is returned. Unlinked elements 
are ignored.&]
[s4; [*C@3 i]-|Position of the element.&]
[s4; [*/ Return value]-|Position of the next element with same value.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 FindLast][%00-00@(64) (][%00-00 const][%00-00@(64) _
][%00-00@4 T][%00-00@(64) `&_][%00-00@3 x][%00-00@(64) , ][%00-00 unsigned][%00-00@(64) _][%00-00@3 `_
hash][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the last element with specified value 
in AIndex, using a precomputed hash value. The precomputed hash 
value must be the same as the hash value that would be the result 
of HashFn. If multi`-key ordering is not broken and more than 
one element with the same value exists in AIndex, the greatest 
position is retrieved. If the specified value does not exist 
in AIndex, a negative number is returned. Unlinked elements are 
ignored.&]
[s4; [*C@3 x]-|Element to find.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the element or negative number if 
value is not in AIndex.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 FindLast][%00-00@(64) (][%00-00 const][%00-00@(64) _
][%00-00@4 T][%00-00@(64) `&_][%00-00@3 x][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the last element with specified value 
in AIndex. If multi`-key ordering is not broken and more than 
one element with the same value exists in AIndex, the greatest 
position is retrieved. If element does not exist in AIndex, a 
negative number is returned. Unlinked elements are ignored.&]
[s4; [*C@3 x]-|Element to find.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the element or negative number if 
value is not in AIndex.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 FindPrev][%00-00@(64) (][%00-00 int][%00-00@(64) _
][%00-00@3 i][%00-00@(64) )_][%00-00 const]&]
[s2; Retrieves the position of the previous element with the same 
value as the element at the specified position. If multi`-key 
ordering is not broken and more than one element with that value 
exists in AIndex, the greatest position lower than specified 
one is retrieved (so that positions got by subsequent calls to 
FindNext are in descending order). When there are no more elements 
with required value, negative number is returned. Unlinked elements 
are ignored.&]
[s4; [*C@3 i]-|Position of the element.&]
[s4; [*/ Return value]-|Position of the previous element with same value.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 FindAdd][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 key][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 `_
hash][%00-00 )]&]
[s2; Retrieves position of first element with specified value in 
AIndex, using a precomputed hash value. Precomputed hash value 
must be same as hash value that would be result of HashFn. If 
multi`-key ordering is not broken and more than one element with 
the same value exists in AIndex, the lowest position is retrieved. 
If element does not exist in AIndex, it is added to AIndex and 
position of this newly added element is returned. Unlinked elements 
are ignored.&]
[s4; [*C@3 key]-|Element to find or add.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the found or added element.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 FindAdd][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 key][%00-00 )]&]
[s2; Retrieves position of first element with specified value in 
AIndex. If multi`-key ordering is not broken and more than one 
element with the same value exists in AIndex, lowest position 
is retrieved. If element does not exist in AIndex, it is added 
to AIndex and position of this newly added element is returned. 
Unlinked elements are ignored.&]
[s4; [*C@3 key]-|Element to find or add.&]
[s4; [*/ Return value]-|Position of the found or added element.&]
[s0;3 &]
[s5;K [%00-00^`:`:AIndex^ AIndex][%00-00 `&_][%00-00@0 operator<<][%00-00 (][%00-00@(0.0.255) c
onst][%00-00 _T`&_][%00-00@3 x][%00-00 )]&]
[s2; Operator replacement of [* void Add(const T`& x)]. By returning 
reference to AIndex it allows adding multiple elements in a single 
expression, thus e.g. allowing to construct a temporary Index 
as part of an expression like Foo((Index<int>() << 1 << 2)).&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 newt]-|Element to be added.&]
[s4; [*/ Return value]-|Reference to AIndex.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Unlink][%00-00 (][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 i][%00-00 )]&]
[s2; Unlinks the element at the specified position. The unlinked 
item stays in AIndex but is ignored by any Find operation.&]
[s4; [*C@3 i]-|Position of item to unlink.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 Put][%00-00 (][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T
][%00-00 `&_][%00-00@3 x][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 `_hash][%00-00 )
]&]
[s2; If there are any unlinked elements in AIndex, one of them is 
replaced by specified value. If there are no unlinked elements, 
the element with the specified value is appended to the end of 
AIndex using [* Add]. The precomputed hash should be same as the 
result of HashFn. The position of the placed element is returned.&]
[s7; Invalidates multi`-key ordering.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 x]-|Element to put into AIndex.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position where the element was placed.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 Put][%00-00 (][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T
][%00-00 `&_][%00-00@3 x][%00-00 )]&]
[s2; If there are any unlinked elements in AIndex, one of them is 
replaced by specified value. If there are no unlinked elements, 
the element with the specified value is appended to the end of 
AIndex using [* Add]. The position of the placed element is returned.&]
[s7; Invalidates multi`-key ordering.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s4; [*C@3 x]-|Element to put into AIndex.&]
[s4; [*/ Return value]-|Position where element is placed.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 FindPut][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 key][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 `_
hash][%00-00 )]&]
[s2; Retrieves the position of the first element with the specified 
value in AIndex, using a precomputed hash value. The precomputed 
hash value must be the same as the hash value that would be the 
result of HashFn. If the specified value does not exist in the 
AIndex, it is placed to it using [* Put(const T`& x, unsigned `_hash).] 
The position of the found or placed element is returned.&]
[s7;~~~.992; Invalidates multi`-key ordering.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 key]-|Element to find or put.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the found or placed element.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 FindPut][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 key][%00-00 )]&]
[s2; Retrieves the position of the first element with the specified 
value in AIndex. If the element does not exist in the AIndex, 
it is placed to it using [* Put(const T`& x).] The position of 
the found or placed element is returned.&]
[s7; Invalidates multi`-key ordering.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 key]-|Element to find or put.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Position of the found or placed element.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Set][%00-00 (][%00-00@(0.0.255) int][%00-00 _][%00-00@3 i
][%00-00 , ][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T][%00-00 `&_][%00-00@3 x][%00-00 , 
][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 `_hash][%00-00 )]&]
[s2; Replaces the element at the specified position with a new element 
with the specified value, using a precomputed hash`-value. Speed 
of this operation depends on the total number of elements with 
the same value as the specified one.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 i]-|Position of the element.&]
[s4; [*C@3 x]-|Value to set.&]
[s4; [*C@3 `_hash]-|Precomputed hash value.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Set][%00-00 (][%00-00@(0.0.255) int][%00-00 _][%00-00@3 i
][%00-00 , ][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T][%00-00 `&_][%00-00@3 x][%00-00 )]&]
[s2; Replaces the element at the specified position with a new element 
with the specified value. Speed of this operation depends on 
total number of elements with the same value as specified the 
specified one.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 i]-|Position of the element.&]
[s4; [*C@3 x]-|Value to set.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 const][%00-00@(64) _T`&_][%00-00@0 operator`[`]][%00-00@(64) (][%00-00 i
nt][%00-00@(64) _][%00-00@3 i][%00-00@(64) )_][%00-00 const]&]
[s2; Returns the element at the specified position.&]
[s4; [*C@3 i]-|Position of the element.&]
[s4; [*/ Return value]-|Constant reference to element.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 GetCount][%00-00@(64) ()_][%00-00 const]&]
[s2; Returns number of elements in AIndex.&]
[s4; [*/ Return value]-|Actual number of elements.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 bool][%00-00@(64) _][%00-00@0 IsEmpty][%00-00@(64) ()_][%00-00 const]&]
[s2; Tests whether AIndex is empty. Same as GetCount() `=`= 0.&]
[s4; [*/ Return value]-|true if AIndex is empty, false otherwise.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Clear][%00-00 ()]&]
[s2; Removes all elements from AIndex.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 ClearIndex][%00-00 ()]&]
[s2; Restores multi`-key ordering.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 UnlinkKey][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 h
][%00-00 )]&]
[s2; Unlinks all elements with specified value using precomputed 
hash`-value. Unlinked elements stay in AIndex but are ignored 
by any Find operations. Precomputed hash value must be same as 
hash value that would be result of HashFn. &]
[s4; [*C@3 k]-|Value of elements to unlink.&]
[s4; [*C@3 h]-|Precomputed hash value.&]
[s4; [*/ Return value]-|Number of elements unlinked.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 UnlinkKey][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 )]&]
[s2; Unlinks all elements with specified value. Unlinked elements 
remain in the AIndex but are ignored by any Find operations.&]
[s4; [*C@3 k]-|Value of elements to unlink.&]
[s4; [*/ Return value]-|Number of elements unlinked.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 bool][%00-00@(64) _][%00-00@0 IsUnlinked][%00-00@(64) (][%00-00 int][%00-00@(64) _
][%00-00@3 i][%00-00@(64) )_][%00-00 const]&]
[s2; Tests whether the element at the specified position is unlinked.&]
[s4; [*C@3 i]-|Position.&]
[s4; [*/ Return value]-|true if element is unlinked.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Sweep][%00-00 ()]&]
[s2; Removes all unlinked elements from AIndex. Complexity of the 
operation depends on the number of elements in AIndex, not on 
the number of unlinked elements. Also restores multi`-key ordering.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Insert][%00-00 (][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 i][%00-00 , ][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 ,
 ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 h][%00-00 )]&]
[s2; Inserts an element with the specified value at the specified 
position, using a precomputed hash value. The precomputed hash 
value must be the same as the hash value that would be the result 
of HashFn. This is a slow operation, especially when combined 
with any search operations.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 i]-|Insert position.&]
[s4; [*C@3 k]-|Element to insert.&]
[s4; [*C@3 h]-|Precomputed hash value.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Insert][%00-00 (][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 i][%00-00 , ][%00-00@(0.0.255) const][%00-00 _][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 )
]&]
[s2; Inserts an element with the specified value at the specified 
position. This is a slow operation, especially when combined 
with any search operations.&]
[s7; Requires T to have deep copy constructor.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 i]-|Insert position.&]
[s4; [*C@3 k]-|Element to insert.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Remove][%00-00 (][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 i][%00-00 )]&]
[s2; Removes the element at the specified position. This is a slow 
operation, especially when combined with any search operations.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 i]-|Position of the element to remove.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Remove][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@(0.0.255) int][%00-00 _`*][%00-00@3 sorted`_list][%00-00 , ][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 count][%00-00 )]&]
[s2; Removes multiple elements from AIndex. Time of operation only 
slightly depends on the number of removed elements. This is a 
slow operation, especially when combined with any search operations.&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 sorted`_list]-|Pointer to array of positions to remove, in 
ascending order.&]
[s4; [*C@3 count]-|Number of elements to remove.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Remove][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00^`:`:Vector^ Vector][%00-00 <][%00-00^int^ int][%00-00 >`&_][%00-00@3 sorted`_list][%00-00 )
]&]
[s2; Removes multiple elements from AIndex. Same as Remove(sorted`_list, 
sorted`_list.GetCount()).&]
[s7; Invalidates iterators to AIndex.&]
[s7; Invalidates references to Index.&]
[s4; [*C@3 sorted`_list]-|Sorted Vector of positions to remove.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 RemoveKey][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 , ][%00-00@(0.0.255) unsigned][%00-00 _][%00-00@3 h
][%00-00 )]&]
[s2; Removes all elements with the specified value using a precomputed 
hash`-value. The precomputed hash value must be the same as the 
hash value that would be the result of HashFn. This is a slow 
operation, especially when combined with any search operations.&]
[s4; [*C@3 k]-|Value of the elements to remove.&]
[s4; [*C@3 h]-|Precomputed hash value.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) int][%00-00 _][%00-00@0 RemoveKey][%00-00 (][%00-00@(0.0.255) const][%00-00 _
][%00-00@4 T][%00-00 `&_][%00-00@3 k][%00-00 )]&]
[s2; Removes all elements with the specified value. This is a slow 
operation, especially when combined with any search operations.&]
[s4; [*C@3 k]-|Value of the elements to remove.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Trim][%00-00 (][%00-00@(0.0.255) int][%00-00 _][%00-00@3 n
][%00-00 )]&]
[s2; Reduces the number of elements in AIndex to the specified number. 
Requested number must be less than or equal to actual number 
of elements in AIndex.&]
[s4; [*C@3 n]-|Requested number of elements.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Drop][%00-00 (][%00-00@(0.0.255) int][%00-00 _][%00-00@3 n
][%00-00 _`=_][%00-00@3 1][%00-00 )]&]
[s2; Drops the specified number of elements from the end of the AIndex 
(same as Trim(GetCount() `- n)).&]
[s4; [*C@3 n]-|Number of elements.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 const][%00-00@(64) _T`&_][%00-00@0 Top][%00-00@(64) ()_][%00-00 const]&]
[s2; Returns a reference to the last element in the AIndex.&]
[s4; [*/ Return value]-|Reference of thr last element in the AIndex.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Reserve][%00-00 (][%00-00@(0.0.255) int][%00-00 _
][%00-00@3 n][%00-00 )]&]
[s2; Reserves capacity. If the requested capacity is greater than 
current capacity, capacity is increased to the requested value.&]
[s4; [*C@3 n]-|Requested capacity.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Shrink][%00-00 ()]&]
[s2; Minimizes the memory consumption of AIndex by decreasing the 
capacity to the number of elements.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 int][%00-00@(64) _][%00-00@0 GetAlloc][%00-00@(64) ()_][%00-00 const]&]
[s2; Returns the current capacity of AIndex.&]
[s4; [*/ Return value]-|Capacity of AIndex.&]
[s0;3 &]
[s5;K [%00-00@(0.0.255) void][%00-00 _][%00-00@0 Serialize][%00-00 (][%00-00^`:`:Stream^ Stream
][%00-00 `&_][%00-00@3 s][%00-00 )]&]
[s2; Serializes content of AIndex to/from Stream. Works only if NTL 
is used as part of UPP.&]
[s7; Requires T to have serialization operator defined.&]
[s4; [*C@3 s]-|Target/source stream.&]
[s0;3 &]
[s5;K [%00-00 V_][%00-00@0 PickKeys][%00-00 ()_pick`_]&]
[s2; Returns a basic random access container of elements. Destroys 
AIndex by picking.&]
[s4; [*/ Return value]-|Basic random access container of elements in 
AIndex.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00 const][%00-00@(64) _V`&_][%00-00@0 GetKeys][%00-00@(64) ()_][%00-00 con
st]&]
[s2; Returns a constant reference to basic random access container 
of elements.&]
[s4; [*/ Return value]-|Constant reference to a basic random access 
container of elements.&]
[s0;3 &]
[s5;K [%00-00^`:`:AIndex^ AIndex][%00-00 `&_][%00-00@0 operator`=][%00-00 (pick`__][%00-00@4 V][%00-00 `&
_][%00-00@3 s][%00-00 )]&]
[s2; Assigns basic random access container to AIndex. Transfers the 
source container in short constant time, but destroys it by picking.&]
[s4; [*C@3 s]-|Source container.&]
[s0;3 &]
[s5;K [%00-00^`:`:AIndex^ AIndex][%00-00 `&_][%00-00@0 operator<<`=][%00-00 (][%00-00@(0.0.255) c
onst][%00-00 _][%00-00@4 V][%00-00 `&_][%00-00@3 s][%00-00 )]&]
[s2; Assigns the basic random access container to AIndex, while preserving 
the value of the source container.&]
[s7; Requires T to have deep copy constructor or optional deep copy.&]
[s4; [*C@3 s]-|Source container.&]
[s0;3 &]
[s0;:`:`:AIndex`:`:AIndex`(pick`_ V`&`): [* AIndex](pick`_ V`& [*@3 s])&]
[s2; Pick`-constructs AIndex from a basic random access container. 
Transfers the source container in short constant time, but destroys 
it by picking.&]
[s4; [*C@3 s]-|Source basic random access container.&]
[s0;3 &]
[s0;:`:`:AIndex`:`:AIndex`(const V`&`,int`): [* AIndex](const V`& [*@3 s], 
int)&]
[s2; Deep`-copy constructs AIndex from basic random access container.&]
[s7; Requires T to have deep copy constructor or optional deep copy 
constructor.&]
[s4; [*C@3 s]-|Source AIndex.&]
[s0;3 &]
[s5;K@0 [%00-00@(64) typedef_T_][%00-00 ValueType]&]
[s2; Typedef of T for use in templated algorithms.&]
[s0;3 &]
[s5;K@0 [%00-00@(64) typedef_typename_][%00-00^V`:`:ConstIterator^@(64) V`::ConstIterator][%00-00@(64) _
][%00-00 ConstIterator]&]
[s2; Constant iterator type.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00^`:`:AIndex`:`:ConstIterator^@(64) ConstIterator][%00-00@(64) _][%00-00@0 B
egin][%00-00@(64) ()_][%00-00 const]&]
[s2; Returns a constant iterator to the first element in AIndex.&]
[s4; [*/ Return value]-|Iterator.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00^`:`:AIndex`:`:ConstIterator^@(64) ConstIterator][%00-00@(64) _][%00-00@0 E
nd][%00-00@(64) ()_][%00-00 const]&]
[s2; Returns a constant iterator to the position just beyond the 
last element in AIndex.&]
[s4; [*/ Return value]-|Iterator.&]
[s0;3 &]
[s5;K@(0.0.255) [%00-00^`:`:AIndex`:`:ConstIterator^@(64) ConstIterator][%00-00@(64) _][%00-00@0 G
etIter][%00-00@(64) (][%00-00 int][%00-00@(64) _][%00-00@3 pos][%00-00@(64) )_][%00-00 const]&]
[s2; Returns a constant iterator to the element at specified position. 
Same as [* Begin() `+ i]. The benefit of this method is that [* pos] 
is range checked in debug mode.&]
[s4; [*C@3 pos]-|Required position.&]
[s4; [*/ Return value]-|Iterator.&]
[s0;3 &]
[s0;:`:`:AIndex`:`:AIndex`(`): [* AIndex]()&]
[s2; Constructor. Constructs an empty AIndex.&]
[s0;3 &]
[s0;:`:`:AIndex`:`:AIndex`(const`:`:AIndex`&`,int`): [* AIndex](const 
[* AIndex]`& [*@3 s], int)&]
[s2; Optional deep copy constructor.&]
[s7; Requires T to have deep copy constructor or optional deep copy 
constructor.&]
[s4; [*C s]-|Source AIndex.&]
[s0; ]