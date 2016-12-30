import os
import sys
import argparse
import subprocess
import hashlib

def get_arg_parser():
	parser = argparse.ArgumentParser("""
Ruleaza testele si afiseaza pentru fiecare:
PASSED	-	a trecut	(out == res)
FAILED	-	a picat		(out != res)
MISSING	-	a picat		(nu s-a scris fisier res)
ERROR	-	eroare in Tester.exe
	""")
	
	parser.add_argument("test", type=int, nargs="?", 
		help="Ruleaza testul TEST. Daca lipseste, ruleaza toate testele."
	)
	parser.add_argument("last", type=int, nargs="?", 
		help="Ruleaza testele de la TEST la LAST"
	)
	
	parser.add_argument("--tester", type=str, metavar="EXECUTABLE", 
		default=os.path.join("code", "Tester", "Tester", "Debug", "Tester.exe"), 
		help="Path-ul executabilului Tester.exe"
	)
	parser.add_argument("--out-dir", type=str, default="out", metavar="DIR", 
		help="Directorul cu fisiere .out"
	)
	parser.add_argument("--res-dir", type=str, default="res", metavar="DIR", 
		help="Directorul cu fisiere .res"
	)
	
	parser.add_argument("--tester-cwd", type=str, metavar="DIR",
		help="Apeleaza Tester.exe din DIR"
	)
	parser.add_argument("--tester-suppress", action="store_true", 
		help="Nu afisa output de la Tester.exe"
	)
	parser.add_argument("--tester-no-run", action="store_true", 
		help="Nu apla Tester.exe, doar compara out cu res"
	)
	parser.add_argument("--tester-each", action="store_true", 
		help="Apeleaza Tester.exe pentru fiecare test in parte"
	)
	
	return parser

def parse_args(args):
	parser = get_arg_parser()
	
	args = parser.parse_args(args)
	
	if not os.path.isfile(args.tester):
		parser.error("Nu am gasit Tester.exe: " + args.tester)
	if not os.path.isdir(args.out_dir):
		parser.error("Nu am gasit directorul out: " + args.out_dir)
	if not os.path.isdir(args.res_dir):
		parser.error("Nu am gasti directorul res: " + args.res_dir)
	
	return args

def md5_from_path(path):
	hash = hashlib.md5()
	with open(path, "rb") as f:
		for chunk in iter(lambda :f.read(4096), b""):
			hash.update(chunk)
	return hash.digest()

def generate_test_files(args):
	if args.test is None:
		for test_file_name in os.listdir(args.out_dir):
			test_name = test_file_name.split(".", 1)[0]
			yield (
				test_name, 
				os.path.join(args.out_dir, test_name + ".out"), 
				os.path.join(args.res_dir, test_name + ".res"), 
			)
	else:
		if args.last is None:
			args.last = args.test + 1
		for test_id in xrange(args.test, args.last):
			test_name = str(test_id).zfill(3)
			yield(
				test_name, 
				os.path.join(args.out_dir, test_name + ".out"), 
				os.path.join(args.out_dir, test_name + ".res"), 
			)

def call_tester(path, test=None, last=None, cwd=None, suppress=False):
	cmd = [path]
	if test is not None:
		cmd.append(str(test))
	else:
		cmd.append("runall")
	if last is not None:
		cmd.append(str(last))
	subprocess.check_call(
		cmd, 
		cwd=cwd, 
		stdout=open(os.devnull) if suppress else None, 
		stderr=open(os.devnull) if suppress else None, 
	)

def main(args):
	if not (args.tester_each or args.tester_no_run):
		try:
			call_tester(args.tester, args.test, args.last, cwd=args.tester_cwd, suppress=args.tester_suppress)
		except:
			print("ERROR: Apel Tester.exe! Incearca optiunea --tester-each")
			return 1
			#raise
	
	for name, out_file, res_file in generate_test_files(args):
		if args.tester_each and not args.tester_no_run:
			try:
				call_tester(args.tester, int(name), cwd=args.tester_cwd, suppress=args.tester_suppress)
			except:
				print("ERROR: " + name)
				continue
		if not os.path.isfile(res_file):
			print("MISSING: " + name)
			continue
		if os.path.getsize(out_file) != os.path.getsize(res_file):
			print("FAILED: " + name)
			continue
		if md5_from_path(out_file) != md5_from_path(res_file):
			print("FAILED: " + name)
			continue
		print("PASSED: " + name)

if __name__ == "__main__":
	exit(main(parse_args(sys.argv[1:])))
