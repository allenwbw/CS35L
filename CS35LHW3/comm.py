#!/usr/bin/python
from optparse import OptionParser
import locale, sys



def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Compare sorted files FILE1 and File2 line by line."""
    
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",action="store_true",dest="column1",default=False,
                      help="suppress column 1")
    parser.add_option("-2",action="store_true",dest="column2",default=False,
                      help="suppress column 2")
    parser.add_option("-3",action="store_true",dest="column3",default=False,
                      help="suppress column 3")
    parser.add_option("-u",action="store_true",dest="unsorted",default=False,
                      help="compare two unsorted files")
    options,args = parser.parse_args(sys.argv[1:])
    if len(args)!=2:
        parser.error("wrong number of operands")
    if args[0] == '-':
        file1=sys.stdin
        list1=file1.readlines()
    else:
        try:
            file1=open(args[0], 'r')
            list1=file1.readlines()
        except IOError as e:
               errno, strerror = e.args
               parser.error("I/O error({0}): {1}".
               format(errno, strerror))
        file1.close()
    if args[1] == '-':
        file2=sys.stdin
        list2=file2.readlines()
    else:
        try:
            file2=open(args[1], 'r')
            list2=file2.readlines()
        except IOError as e:
            errno, strerror = e.args
            parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

        file2.close()
    if not options.unsorted:
        for index in range(len(list1)-1):
            if list1[index]>list1[index+1]:
                parser.error("FILE1 not sorted")
        for index in range(len(list2)-1):
            if list2[index]>list2[index+1]:
                parser.error("FILE2 not sorted")
    if options.unsorted :
        sortedlist1=sorted(list1)
        sortedlist2=sorted(list2)
    else:
        sortedlist1=list1
        sortedlist2=list2
    i=0
    j=0
    total=len(sortedlist1)+len(sortedlist2)
    common=[]
    while i+j<total and i<len(sortedlist1) and j<len(sortedlist2):
        if sortedlist1[i]<sortedlist2[j]:
            if not options.column1 and not options.unsorted:
                sys.stdout.write(sortedlist1[i])
            i+=1
        if i==len(sortedlist1):
            break
        if sortedlist1[i]>sortedlist2[j]:
            if not options.column2 and not options.unsorted:
                sys.stdout.write("        "+sortedlist2[j])
            j+=1
        if j==len(sortedlist2):
            break
        if sortedlist1[i]==sortedlist2[j]:
            if not options.column3 and not options.unsorted:
                sys.stdout.write("                "+sortedlist1[i])
            common.append(sortedlist1[i])
            i+=1
            j+=1
        if not options.unsorted and i+j==total or i==len(sortedlist1) or j==len(sortedlist2):
            sys.stdout.write("\n")
        
    while i<len(sortedlist1):
        if not options.column1 and not options.unsorted:
            sys.stdout.write(sortedlist1[i])
        i+=1
        if i==len(sortedlist1) and not options.unsorted and not options.column1:
            sys.stdout.write("\n")
    while j<len(sortedlist2):
        if not options.column2 and not options.unsorted:
            sys.stdout.write("        "+sortedlist2[j])
        j+=1
        if j==len(sortedlist2) and not options.unsorted and not options.column2:
            sys.stdout.write("\n")
    i=0
    commoncopy=list(common)
    while i<len(list1) and options.unsorted:
        if list1[i] in common and not options.column3:
            sys.stdout.write("                "+list1[i])
            common.remove(list1[i])
            i+=1
            if i==len(list1):
                sys.stdout.write("\n")
            continue
        if not list1[i] in common and not options.column1:
            sys.stdout.write(list1[i])
        i+=1
        if i==len(list1):
            sys.stdout.write("\n")
    i=0
    while i<len(commoncopy) and options.unsorted:
        list2.remove(commoncopy[i])
        i+=1   
    i=0
    while i<len(list2) and options.unsorted and not options.column2:
        sys.stdout.write("        "+list2[i])
        i+=1


if __name__ == "__main__":
    main()

    
