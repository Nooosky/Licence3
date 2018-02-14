<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="distinct-v0.xsl"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="sf-1">
    <xsl:apply-templates select="entries"/>
  </xsl:template>

  <xsl:template match="books | inproceedings">
    <xsl:variable name="the-title" select="title"/>
    <xsl:variable name="other-nb-with-some-title" select="count(preceding-sibling::*[string(title) = $the-title] |
      following-sibling::*[string(title) = $the-title])"/>
    <xsl:value-of select="concat($the-title, ' ', $other-nb-with-some-title, eol)"/>
  </xsl:template>

</xsl:stylesheet>
