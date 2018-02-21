<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="books-1"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:key name="same-title" match="title" use="normalize-space(string())"/>




  <xsl:template match="sf-1">
    <xsl:apply-templates select="entries"/>
  </xsl:template>

  <xsl:template match="entries">
    <xsl:apply-templates select="book|improceedings">
    <!--<xsl:sort select="position()" order="descending"/>
    <xsl:sort select="id(author/personrefs/@to)[1]/last"/>
    <xsl:sort select="id(author/personrefs/@to)[1]/first"/>-->
    <xsl:sort select="title/text()"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="book|improceedings">
    <xsl:apply-templates select="title"/>
  </xsl:template>

  <xsl:template match="title">
    <xsl:variable name="the-normalised-title" select="normalize-space(string())"/>
    <xsl:variable name="nb" select="count(key('same-title', $the-normalised-title))-1" as="xsd:integer"/>
    <xsl:value-of select=" $the-normalised-title, ' -- ', if ($nb eq 0) then 'Unique title' else ($nb, ' other occurences'), $eol" separator=""/>
  </xsl:template>


  </xsl:stylesheet>
