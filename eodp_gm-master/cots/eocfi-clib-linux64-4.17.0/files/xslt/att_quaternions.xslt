<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:n1="http://eop-cfi.esa.int/CFI" exclude-result-prefixes="n1">	
	<xsl:variable name="XML" select="/"/>	
	<xsl:template match="/">
		<html>
			<head>
				<title/>
				<style type="text/css">
					table {
  margin-top: 0.75em;
  margin-bottom: 0.75em;
}
table, tr, th, td {
  border-collapse:collapse;
  border: 1px solid black;
  white-space: nowrap;
}
table.header, table.summary2, table.events, table.reports, table.cadus, table.vcdus, table.isps {
  width: 90%;
}
th, td {
  padding-left: 10px;
  padding-right: 10px;
}
th {
  background-color: #9acd32;
}

tr:nth-child(odd) {
  background-color:#eeeeee;
}
tr:nth-child(even) {
  background-color:#ffffff;
}

/* Sorting */
th.table-sortable {
  cursor:pointer;
  background-image:url(".xsl/icons/sortable.gif");
  background-position:center left;
  background-repeat:no-repeat;
  padding-left:12px;
}
th.table-sorted-asc {
  background-image:url(".xsl/icons/sorted_up.gif");
  background-position:center left;
  background-repeat:no-repeat;
}
th.table-sorted-desc {
  background-image:url(".xsl/icons/sorted_down.gif");
  background-position:center left;
  background-repeat:no-repeat;
}
th.table-filtered {
  background-image:url(".xsl/icons/filter.gif");
  background-position:center left;
  background-repeat:no-repeat;
}
select.table-autofilter {
  font-size:smaller;
} 

body {
  padding-left:40px;
  padding-top:20px;
  padding-bottom:80px;
}

.small-link {
  font-size:70%;
  padding-left:10px;
}
				</style>
				<script type="text/javascript">

function createLink(href, innerHTML) {
	var a = document.createElement(&quot;a&quot;);
	a.setAttribute(&quot;href&quot;, href);
	a.innerHTML = innerHTML;
	return a;
}

function generateTOC(toc) {
	var tocHeader = document.createElement(&quot;h3&quot;);
	tocHeader.innerHTML = &quot;&lt;a name=\&quot;toc\&quot;&gt;Table of contents&lt;/a&gt;&quot;;
	toc.appendChild(tocHeader);
	toc = toc.appendChild(document.createElement(&quot;ul&quot;));
	var previousNode, previousSection = &quot;toc&quot;, previousLinks, previousHeading;
	for (var i = 0; i &lt; document.body.childNodes.length; ++i) {
		var node = document.body.childNodes[i];
		if (node.nodeName.toLowerCase() == &quot;h3&quot;) {
			var sectionLink = node.innerHTML.replace(/ /g,&quot;_&quot;);
			toc.appendChild(h3item = document.createElement(&quot;li&quot;)).appendChild(createLink(&quot;#&quot; + sectionLink, node.innerHTML));
			var currentLinks = &quot;&lt;a class=\&quot;small-link\&quot; href=\&quot;#&quot; + previousSection + &quot;\&quot;&gt;&amp;laquo; prev.&lt;/a&gt;&quot;
				+ &quot;&lt;span class=\&quot;small-link\&quot;&gt;&amp;bull;&lt;/span&gt;&quot;
				+ &quot;&lt;a class=\&quot;small-link\&quot; href=\&quot;#toc\&quot;&gt;TOC&lt;/a&gt;&quot;;
			var currentHeading = &quot;&lt;a name=\&quot;&quot; + sectionLink + &quot;\&quot;&gt;&quot; + node.innerHTML + &quot;&lt;/a&gt;&quot;;
			node.innerHTML = &quot;&lt;p&gt;&quot; + currentLinks + &quot;&lt;/p&gt;&quot; + currentHeading
			if (previousNode) {
				previousNode.innerHTML = &quot;&lt;p&gt;&quot; + previousLinks
					+ &quot;&lt;span class=\&quot;small-link\&quot;&gt;&amp;bull;&lt;/span&gt;&quot;
					+ &quot;&lt;a class=\&quot;small-link\&quot; href=\&quot;#&quot; + sectionLink + &quot;\&quot;&gt;next &amp;raquo;&lt;/a&gt;&quot;
					+ &quot;&lt;/p&gt;&quot; + previousHeading;
			}
			previousHeading = currentHeading;
			previousLinks = currentLinks;
			previousNode = node;
			previousSection = sectionLink;
		}
	}
}

				</script>
			</head>
			<body onload="generateTOC(document.getElementById(&apos;toc&apos;));">
				<xsl:for-each select="$XML">
					<h2>
						<span style="font-weight:bold; ">
							<xsl:text>Attitude file with quaternions</xsl:text>
						</span>
						<span>
							<xsl:text> (style sheet version 1.0)</xsl:text>
						</span>
					</h2>
					<xsl:for-each select="n1:Earth_Explorer_File">
						<br/>
						<xsl:element name="div">
							<xsl:attribute name="id">
								<xsl:value-of select="'toc'"/>
							</xsl:attribute>
						</xsl:element>
						<br/>
						<h3>Header</h3>
						<table border="1" cellpadding="5" cellspacing="0">
							<xsl:variable name="CurrContextGrid_0" select="."/>
							<tbody>
								<tr>
									<th>
										<span>
											<xsl:text>Schema version</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="$XML">
													<xsl:for-each select="n1:Earth_Explorer_File">
														<xsl:for-each select="@schemaVersion">
															<span>
																<xsl:value-of select="string(.)"/>
															</span>
														</xsl:for-each>
													</xsl:for-each>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>File_Name</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:File_Name">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>File_Description</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:File_Description">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>Notes</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:Notes">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>Mission</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:Mission">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>File_Class</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:File_Class">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>File_Type</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:File_Type">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>Validity_Period</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<table border="0" cellpadding="5" cellspacing="0">
													<xsl:variable name="CurrContextGrid_1" select="."/>
													<tbody>
														<tr>
															<th>
																<span>
																	<xsl:text>Validity_Start</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Validity_Period">
																<td>
																	<xsl:for-each select="n1:Validity_Start">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
														<tr>
															<th>
																<span>
																	<xsl:text>Validity_Stop</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Validity_Period">
																<td>
																	<xsl:for-each select="n1:Validity_Stop">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
													</tbody>
												</table>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>File_Version</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<xsl:for-each select="n1:File_Version">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
								<tr>
									<th>
										<span>
											<xsl:text>Source</xsl:text>
										</span>
									</th>
									<xsl:for-each select="n1:Earth_Explorer_Header">
										<xsl:for-each select="n1:Fixed_Header">
											<td>
												<table border="0" cellpadding="5" cellspacing="0">
													<xsl:variable name="CurrContextGrid_2" select="."/>
													<tbody>
														<tr>
															<th>
																<span>
																	<xsl:text>System</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Source">
																<td>
																	<xsl:for-each select="n1:System">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
														<tr>
															<th>
																<span>
																	<xsl:text>Creator</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Source">
																<td>
																	<xsl:for-each select="n1:Creator">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
														<tr>
															<th>
																<span>
																	<xsl:text>Creator_Version</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Source">
																<td>
																	<xsl:for-each select="n1:Creator_Version">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
														<tr>
															<th>
																<span>
																	<xsl:text>Creation_Date</xsl:text>
																</span>
															</th>
															<xsl:for-each select="n1:Source">
																<td>
																	<xsl:for-each select="n1:Creation_Date">
																		<xsl:apply-templates/>
																	</xsl:for-each>
																</td>
															</xsl:for-each>
														</tr>
													</tbody>
												</table>
											</td>
										</xsl:for-each>
									</xsl:for-each>
								</tr>
							</tbody>
						</table>
						<xsl:for-each select="n1:Data_Block">
							<br/>
							<h3>Data Block</h3>
							<br/>
							<table border="1" cellpadding="5" cellspacing="0">
								<xsl:variable name="CurrContextGrid_3" select="."/>
								<tbody>
									<tr>
										<th>
											<span>
												<xsl:text>type</xsl:text>
											</span>
										</th>
										<td>
											<xsl:for-each select="@type">
												<span>
													<xsl:value-of select="string(.)"/>
												</span>
											</xsl:for-each>
										</td>
									</tr>
									<tr>
										<th>
											<span>
												<xsl:text>Attitude_File_Type</xsl:text>
											</span>
										</th>
										<td>
											<xsl:for-each select="n1:Attitude_File_Type">
												<xsl:apply-templates/>
											</xsl:for-each>
										</td>
									</tr>
									<tr>
										<th>
											<span>
												<xsl:text>Attitude_Data_Type</xsl:text>
											</span>
										</th>
										<td>
											<xsl:for-each select="n1:Attitude_Data_Type">
												<xsl:apply-templates/>
											</xsl:for-each>
										</td>
									</tr>
									<tr>
										<th>
											<span>
												<xsl:text>Max_Gap</xsl:text>
											</span>
										</th>
										<td>
											<xsl:for-each select="n1:Max_Gap">
												<xsl:apply-templates/>
											</xsl:for-each>
											<span>
												<xsl:text> [</xsl:text>
											</span>
											<xsl:for-each select="n1:Max_Gap">
												<xsl:for-each select="@unit">
													<span>
														<xsl:value-of select="string(.)"/>
													</span>
												</xsl:for-each>
											</xsl:for-each>
											<span>
												<xsl:text>]</xsl:text>
											</span>
										</td>
									</tr>
								</tbody>
							</table>
							<xsl:for-each select="n1:Quaternion_Data">
								<br/>
								<h3>Quaternion Data</h3>
								<table border="1" cellpadding="5" cellspacing="0">
									<xsl:variable name="CurrContextGrid_4" select="."/>
									<tbody>
										<tr>
											<th>
												<span>
													<xsl:text>Reference_Frame</xsl:text>
												</span>
											</th>
											<td>
												<xsl:for-each select="n1:Reference_Frame">
													<xsl:apply-templates/>
												</xsl:for-each>
											</td>
										</tr>
									</tbody>
								</table>
								<h3>List of Quaternions</h3>
								<br/>
								<xsl:for-each select="n1:List_of_Quaternions">
									<table border="1" cellpadding="5" cellspacing="0">
										<xsl:variable name="CurrContextGrid_5" select="."/>
										<thead>
											<tr>
												<th colspan="2">
													<span>
														<xsl:text>Time</xsl:text>
													</span>
												</th>
												<th>
													<span>
														<xsl:text>Q1</xsl:text>
													</span>
												</th>
												<th>
													<span>
														<xsl:text>Q2</xsl:text>
													</span>
												</th>
												<th>
													<span>
														<xsl:text>Q3</xsl:text>
													</span>
												</th>
												<th>
													<span>
														<xsl:text>Q4</xsl:text>
													</span>
												</th>
											</tr>
										</thead>
										<tbody>
											<xsl:for-each select="n1:Quaternions">
												<tr>
													<td style="text-align:right; ">
														<xsl:for-each select="n1:Time">
															<xsl:apply-templates/>
														</xsl:for-each>
													</td>
													<td style="text-align:center; ">
														<xsl:for-each select="n1:Time">
															<xsl:for-each select="@ref">
																<span>
																	<xsl:value-of select="string(.)"/>
																</span>
															</xsl:for-each>
														</xsl:for-each>
													</td>
													<td style="text-align:right; ">
														<xsl:for-each select="n1:Q1">
															<xsl:apply-templates/>
														</xsl:for-each>
													</td>
													<td style="text-align:right; ">
														<xsl:for-each select="n1:Q2">
															<xsl:apply-templates/>
														</xsl:for-each>
													</td>
													<td style="text-align:right; ">
														<xsl:for-each select="n1:Q3">
															<xsl:apply-templates/>
														</xsl:for-each>
													</td>
													<td style="text-align:right; ">
														<xsl:for-each select="n1:Q4">
															<xsl:apply-templates/>
														</xsl:for-each>
													</td>
												</tr>
											</xsl:for-each>
										</tbody>
									</table>
								</xsl:for-each>
							</xsl:for-each>
						</xsl:for-each>
						<br/>
					</xsl:for-each>
					<br/>
				</xsl:for-each>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
