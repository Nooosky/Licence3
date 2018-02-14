<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="q3_1"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="sf-1">
    <xsl:apply-templates select="entries"/>
  </xsl:template>

  <xsl:template match="entries">
    <xsl:apply-templates select="book"/>
  </xsl:template>

  <xsl:template match="book">

    <xsl:apply-templates select="title"/>
    <xsl:apply-templates select="publisher"/>
    <xsl:apply-templates select="year"/>
    <xsl:apply-templates select="$eol"/>

  </xsl:template>

</xsl:stylesheet>
