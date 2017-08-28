###############################
# Class to hold data for HSP, #
#  SAM, and coord/delta files #
#                             #
# @ Audrey and Carolina, 2017 #
###############################

class Alignment:
	__slots__ = ["rname", "rstart", "rend", "rlen", "rcov"
	             "qname", "qstart", "qend", "qlen", "qcov",
	             "pid"]
	
	def __init__(self, rname, qname, rstart, rend, qstart, qend, \
			rlen, qlen, rcov, qcov, pid):
		self.rname = rname
		self.qname = qname
		self.rstart = long(rstart)
		self.rend = long(rend)
		self.qstart = long(qstart)
		self.qend = long(qend) # for sam data, stores the qalen since information of the query is not given
		self.rlen = long(rlen)
		self.qlen = long(qlen)
		self.rcov = float(rcov)
		self.qcov = float(qcov)
		self.pid = float(pid) # for sam data, this value stores the MapQ, not the pid since the pid is calculated differently depending on the version of SAM used
		
	def __str__(self):
		return "{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n".format(self.rname, self.qname, self.rstart, self.rend, self.qstart, self.qend, self.rlen, self.qlen, self.rcov, self.qcov, self.pid)
	
	# to be used by Comparison
	def get_ref_name(self):
		return self.rname
	
	def get_query_name(self):
		return self.qname
	
	def get_ref_coverage(self):
		return self.rcov
	
	def get_query_coverage(self):
		return self.qcov
		
	def get_percent_id(self):
		return self.pid
		
	def get_left_most_position(self):
		return self.rstart if self.rend > self.rstart else self.rend	
	
	def get_right_most_position(self):
		return self.rstart if self.rend < self.rstart else self.rend	
	
	def get_r_coords(self):
		return (self.rstart, self.rend)

	def get_r_coords_qname(self):
		return (self.rstart,self.rend,self.qname)

	def get_q_coords(self):
		return (self.qstart,self.qend)

	def get_rlen(self):
		return self.rlen
	
	def get_qlen(self):
		return self.qlen



#Similar to All_Alignment objects but only stores info needed for a merged alignment
# from what I can gather, this holds the info for merged alignments:
#    given a reference, this class has all of the overlapping queries that aligned to the reference
#    and the start and stop points of this merged alignment
class Constructed_Alignment:
	
	__slots__ = ["rname", "qname", "rstart", "rstop", "id_list", "rlen", "arlen", "cov", "label"]
	
	def __init__(self, rname, qname, rstart, rstop, id1, rlen, label=None):
		self.rname = rname
		self.qname = qname
		self.rstart = long(rstart)
		self.rstop = long(rstop)
		self.arlen = rstop - rstart # the alignment length of the reference sequence
		self.rlen = rlen 
		self.cov = self.arlen / float(self.rlen)
		self.label = label
		self.id_list = [id1] # list of queries that are part of this merged alignment
		self.ann_dict = dict() # dictionary of { qname : (pcov, annotation_label) }

	def __repr__(self):
		if self.label == "UAR" or self.label == "UAQ":
			return "{}\t{}\t{}\t{}\t{}\n".format(self.rname, self.qname, self.rstart, self.rstop, self.label)   
		else:
			return_str = ""
			base_str = "{}\t{}\t{}\t{}".format(self.rname, self.qname, self.rstart, self.rstop)
			for ann_q, pct_label in  self.ann_dict.items():
				return_str += base_str + "\t" + ann_q + "\t" + str(pct_label[1]) + "\t" + str(pct_label[0]) + "\n"
			return return_str   

			
	def get_ref_name(self):
		return self.rname
	
	def get_query_name(self):
		return self.qname
		
	def get_left_most_position(self):
		return self.rstart if self.rstop > self.rstart else self.rstop	
	
	def get_right_most_position(self):
		return self.rstart if self.rstop < self.rstart else self.rstop	
	
	def get_r_coords(self):
		return (self.rstart,self.rstop)

	def set_r_coords(self, start, end):
		self.rstart = long(start)
		self.rstop = long(end)
		self.arlen = self.rstop - self.rstart

	def add_id(self, id):
		self.id_list.append(id)

	def get_rlen(self):
		return self.rlen
	
	def get_arlen(self):
		return self.arlen
	
	def get_cov(self):
		return self.cov
	
	def set_label(self, new_label):
		self.label = new_label
		
	def get_label (self):
		return self.label

	def add_annotation(self, q2name, label, percent):
		self.ann_dict[q2name] = (percent, label)

	def get_ann_dict(self):
		return self.ann_dict
